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
	{ 0x3e0fecb8, "module_layout" },
	{ 0x37a0cba, "kfree" },
	{ 0xa58b498f, "class_destroy" },
	{ 0xce789fbc, "device_destroy" },
	{ 0x9a7ec654, "kmem_cache_alloc_trace" },
	{ 0xc3023b5d, "kmalloc_caches" },
	{ 0xe0ac035a, "device_create" },
	{ 0xa4e8f334, "__class_create" },
	{ 0x687e9f04, "cdev_del" },
	{ 0x911cfbec, "cdev_add" },
	{ 0xd7b314c, "cdev_init" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x95e7ca8b, "cdev_alloc" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x75bb675a, "finish_wait" },
	{ 0x4292364c, "schedule" },
	{ 0x622fa02a, "prepare_to_wait" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xe45f60d8, "__wake_up" },
	{ 0x37ff4c06, "copy_from_user_overflow" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0xf5cc4f41, "module_refcount" },
	{ 0x62ef882c, "current_task" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "4724363AAD0D51F9383DC84");
