#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x141d70f7, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9f070ae, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x92d191a6, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xc9053c8d, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x884c7ac4, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x7762a55b, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x7df4a18f, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x50304a4b, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x7b9bf04a, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xf88545e4, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xd9aee5e6, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0xb8b6150f, __VMLINUX_SYMBOL_STR(kill_fasync) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x8e7ff0de, __VMLINUX_SYMBOL_STR(module_refcount) },
	{ 0xcda60f48, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0xefc4bac0, __VMLINUX_SYMBOL_STR(fasync_helper) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "193C0FA166EA66680546F69");
