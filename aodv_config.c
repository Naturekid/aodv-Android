/***************************************************************************
aodv_config.h  -  description
-------------------
begin                : FRI NOV 14 2014
copyright            : (C) 2014 by Cai Bingying
email                :
***************************************************************************/
#include "aodv_config.h"

#define max_dev_num 10


extern aodv_dev *net_dev_list;
extern aodv_route *g_local_route;
extern u_int8_t g_routing_metric;
extern u_int32_t g_node_name;

u_int32_t local_ip_list[max_dev_num];

int get_node_type()
{
	int i_wireless=0;
	int i_wired=0;

	aodv_dev *tmp_dev = net_dev_list;
	g_node_name = tmp_dev->ip;	
	
	while(tmp_dev)
	{
		//record the ips of all netdevices
		//element 0 is the num of ip 
		local_ip_list[i_wireless+i_wired+1] = tmp_dev->ip;
		//set the name of node as the smallest ip
		if(g_node_name > tmp_dev->ip)
			g_node_name = tmp_dev->ip;
		if(strcmp(tmp_dev->name,"adhoc0")==0)
			i_wireless ++;
		else if(strncmp(tmp_dev->name,"eth",3)==0)
			i_wired ++;
#ifdef	DEBUG2
	printk("==========dev:%s	%s============\n",tmp_dev->name,inet_ntoa(tmp_dev->ip));
#endif
		tmp_dev = tmp_dev->next;
	}
	
	local_ip_list[0] = i_wireless + i_wired;
	
	if(i_wireless>0 && i_wired==0)
		return MN_NODE;
	else if(i_wireless==0 && i_wired>0)
		return WDN_NODE;
	else if(i_wireless>0 && i_wired>0)
		return ICN_NODE;
	return 0;
}

bool is_local_ip(u_int32_t ip)
{
	int i = 1;
	printk("ip:%s\n",inet_ntoa(ip));
	while(i <= local_ip_list[0])
	{
		printk("-------------%sin is_local_ip------------\n",inet_ntoa(local_ip_list[i]));
		if( ip==local_ip_list[i] )
			return true;
		i++;
	}
	return false;

}

int route_neigh(u_int32_t src_ip, u_int32_t dst_ip, unsigned char tos)
{
	printk("task route neigh\n");
	extern u_int8_t g_node_type;
	aodv_neigh *tmp_neigh = find_aodv_neigh(dst_ip);
	
	aodv_route *tmp_route;
	if( (tmp_neigh->neigh_type != ICN_NODE) || (g_node_type != ICN_NODE) )
	{
		rreq_aodv_route(src_ip,dst_ip,tos,tmp_neigh,1,g_local_route->dst_seq,tmp_neigh->dev,g_routing_metric);
		
	}
	else
	{
		if( strncmp(tmp_neigh->dev->name,"eth",3)==0 )
		{			
			rreq_aodv_route(src_ip,dst_ip,tos,tmp_neigh,1,g_local_route->dst_seq,tmp_neigh->dev,g_routing_metric);
		}
		else
		{	
			printk("----------hehe---------\n");
			aodv_neigh *better = get_better_link(tmp_neigh);
			if(better)	
			{
				if(rreq_aodv_route(src_ip,dst_ip,tos,better,1,g_local_route->dst_seq,better->dev,g_routing_metric))
				printk("---------better:%s--------\n",inet_ntoa(better->ip));
			}
			else
				rreq_aodv_route(src_ip,dst_ip,tos,tmp_neigh,1,g_local_route->dst_seq,tmp_neigh->dev,g_routing_metric);

		}
		printk("---------%s--------\n",inet_ntoa(tmp_neigh->ip));	
	}
	

	tmp_route = find_aodv_route(src_ip,dst_ip,tos);
	if (tmp_route == NULL) 
		return 0;
	
	tmp_route->num_hops = 1;
	tmp_route->path_metric = 1;
	tmp_route->state = ACTIVE;
	tmp_route->neigh_route = TRUE;
	tmp_route->self_route = TRUE;
	
	src_list_entry *tmp_src_entry = find_src_list_entry(src_ip);
		if (tmp_src_entry == NULL)
			return 0;	
	int error = rpdb_route(RTM_NEWROUTE, tmp_src_entry->rt_table, 0, src_ip,
			tmp_route->next_hop, tmp_route->next_hop, tmp_route->dev->index, 1);

	if (error < 0) {
		printk(
				"Error sending with rtnetlink - Insert Route - err no: %d\n",
				error);
		kfree(tmp_route);
		return 0;

	}


	return 1;

}


