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
	{ 0x8ca33160, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xe07d74d6, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0xcd07ad5b, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x3f38b220, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xdf530d16, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x8c32ce45, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x56b70ba4, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x14a2f48d, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xe989a2f5, __VMLINUX_SYMBOL_STR(gpiod_get_raw_value) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xcd412cb8, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value) },
	{ 0xf63fab98, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x8f678b07, __VMLINUX_SYMBOL_STR(__stack_chk_guard) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

