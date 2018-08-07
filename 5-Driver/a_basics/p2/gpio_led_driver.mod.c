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
	{ 0x7ba76658, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xb4c7262, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x9d63539a, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x31d238f4, __VMLINUX_SYMBOL_STR(gpiod_export) },
	{ 0x97ee57cb, __VMLINUX_SYMBOL_STR(gpiod_direction_output_raw) },
	{ 0x47229b5c, __VMLINUX_SYMBOL_STR(gpio_request) },
	{ 0xb5bfc612, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xad25c456, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x787ec31d, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x2528437c, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x5b4e716d, __VMLINUX_SYMBOL_STR(of_property_read_u32_array) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa2be262, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xd49a3fb4, __VMLINUX_SYMBOL_STR(gpiod_get_raw_value) },
	{ 0x2a7d0fbc, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0x8f678b07, __VMLINUX_SYMBOL_STR(__stack_chk_guard) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x401052cf, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x463b8bd1, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x40780d27, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cmy-led-driver*");