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
	{ 0xab465258, "module_layout" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xf7267d89, "cdev_del" },
	{ 0xe865f196, "cdev_add" },
	{ 0x33f0e9a7, "cdev_init" },
	{ 0x30551482, "cdev_alloc" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0x37ff4c06, "copy_from_user_overflow" },
	{ 0x50eedeb8, "printk" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "C63A1B5E153BA8C04E63B65");
