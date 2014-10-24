#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x5cd0ddfc, "module_layout" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x41960b06, "sock_setsockopt" },
	{ 0x349cba85, "strchr" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xc996d097, "del_timer" },
	{ 0x97255bdf, "strlen" },
	{ 0xd442b3f4, "_raw_write_lock_irqsave" },
	{ 0x79aa04a2, "get_random_bytes" },
	{ 0x31b5d6b6, "malloc_sizes" },
	{ 0xe171397c, "sock_release" },
	{ 0xbf1ff95e, "dst_release" },
	{ 0x8bd94317, "_raw_spin_lock_bh" },
	{ 0x99910908, "icmp_send" },
	{ 0x4f93fb5, "dev_get_by_name" },
	{ 0x3a8ad4dc, "interruptible_sleep_on" },
	{ 0x939f3d11, "remove_proc_entry" },
	{ 0x4986ef98, "nf_reinject" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0xb192d2da, "nf_register_hook" },
	{ 0x91715312, "sprintf" },
	{ 0x48700b84, "kthread_create_on_node" },
	{ 0x7d11c268, "jiffies" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x77339464, "_raw_write_unlock_irqrestore" },
	{ 0x41e92619, "__init_waitqueue_head" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0x72aa82c6, "param_ops_charp" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xbcf2dc5, "proc_mkdir" },
	{ 0x11089ac7, "_ctype" },
	{ 0x27e1a049, "printk" },
	{ 0x58f38c7d, "sock_sendmsg" },
	{ 0x328a05f1, "strncpy" },
	{ 0x876506ac, "nf_unregister_queue_handler" },
	{ 0x8834396c, "mod_timer" },
	{ 0x3ff87dcd, "init_net" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0x61651be, "strcat" },
	{ 0xaca37af7, "_raw_read_lock_irqsave" },
	{ 0xc51ba247, "nf_register_queue_handler" },
	{ 0x80497cf6, "unregister_sysctl_table" },
	{ 0xb368ec89, "_raw_spin_unlock_bh" },
	{ 0xa882d544, "_raw_read_unlock_irqrestore" },
	{ 0xc1ae29a4, "create_proc_entry" },
	{ 0xcba1b035, "wake_up_process" },
	{ 0xb9012926, "kmem_cache_alloc_trace" },
	{ 0x1176e07f, "__per_cpu_offset" },
	{ 0x5b5fc2b4, "ip_route_output_flow" },
	{ 0x72542c85, "__wake_up" },
	{ 0xf6ebc03b, "net_ratelimit" },
	{ 0xb8ea6565, "_raw_write_unlock_bh" },
	{ 0x1d2e87c6, "do_gettimeofday" },
	{ 0xf40946d6, "nf_unregister_hook" },
	{ 0xee3b5c62, "_raw_read_lock_bh" },
	{ 0x874be1d6, "_raw_read_unlock_bh" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0xf59f197, "param_array_ops" },
	{ 0xd51c7659, "interruptible_sleep_on_timeout" },
	{ 0xa4fc2b64, "sock_create" },
	{ 0x6d09b57e, "_raw_write_lock_bh" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xc3fe87c8, "param_ops_uint" },
	{ 0xe914e41e, "strcpy" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "E665FD29E4B48D2764BC442");
