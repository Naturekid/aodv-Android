/***************************************************************************
 Created by Cai Bingying- Version: Sun Dec 21 2014
 ***************************************************************************/
#include "tcnp.h"

//gen route redirection packet
int gen_tcnp(u_int32_t src_ip,u_int32_t dst_ip,u_int32_t last_hop,unsigned char tos){
	
#ifdef DEBUG2
    	char src[20];
    	char dst[20];
    	strcpy(src,inet_ntoa(src_ip));
	strcpy(dst,inet_ntoa(dst_ip));
    printk("----------------in gen tcnp(%s   %s)----------------\n",src,dst);
#endif
	tcnp *tmp_tcnp;
	
	if ((tmp_tcnp = (tcnp *) kmalloc(sizeof(tcnp), GFP_ATOMIC)) == NULL) {
#ifdef DEBUG2
		printk("Can't allocate new tcnp\n");
#endif
		return 0;
	}

	tmp_tcnp->type = TCNP_MESSAGE;
	tmp_tcnp->dst_count = 0;
	tmp_tcnp->reserved = 0;
	tmp_tcnp->n = 0;
	tmp_tcnp->num_hops = 0;
	tmp_tcnp->dst_ip = dst_ip;
	tmp_tcnp->src_ip = src_ip;
	tmp_tcnp->tos = tos;

	send_message(last_hop, NET_DIAMETER, tmp_tcnp,sizeof(tcnp),NULL);
	kfree(tmp_tcnp);
					
	return 1;

}

int recv_tcnp(task *tmp_packet){

	aodv_route *tmp_route;
	tcnp *tmp_tcnp;
	int num_hops;

	tmp_tcnp = (tcnp *) tmp_packet->data;
	num_hops = tmp_tcnp->num_hops+1;

#ifdef DEBUG2
	printk("Recieved a topology change notification packet from %s\n", inet_ntoa(tmp_packet->src_ip));
#endif

    	tmp_route = find_aodv_route(tmp_tcnp->src_ip,tmp_tcnp->dst_ip,tmp_tcnp->tos);

	if (tmp_route && tmp_route->next_hop == tmp_packet->src_ip) {
		//if there is any hop before me
		if(!(is_local_ip(tmp_route->src_ip) || (tmp_route->src_ip == g_null_ip && g_aodv_gateway) )){

			if (tmp_route->state != INVALID) { //route with active traffic

				tmp_tcnp->num_hops = num_hops;
								
				aodv_dev *tmp_dev = get_netdev_by_name(tmp_packet->dev->name);

				send_message(tmp_route->last_hop, NET_DIAMETER, tmp_tcnp,
						sizeof(tcnp),tmp_dev);

#ifdef DEBUG2
	char last[20];
	strcpy(last,inet_ntoa(tmp_route->last_hop));
	printk("--------------------------------------------\n");
	printk("the last hop is %s\n",last);
	printk("--------------------------------------------\n");
#endif

			}//Valid

		}//not the source
		else{

#ifdef DEBUG2
			printk("------------I am the tcnp source-----------");
#endif
			task *new_task;
			new_task = create_task(TASK_GEN_RRRP);
			new_task->src_ip = source;
			new_task->dst_ip = destination;
			new_task->tos = ip->tos;
			insert_task_at_front(new_task);
				
#endif
		    	kfree(tmp_tcnp);
		}//the source

		

	}
	
	return 1;

}

