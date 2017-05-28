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
	{ 0x5306156e, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xb9d58a39, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0xf5c35834, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xbb0c38f9, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x5952a882, __VMLINUX_SYMBOL_STR(__raw_spin_lock_init) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3698c8a4, __VMLINUX_SYMBOL_STR(_raw_spin_trylock) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
	{ 0xb2f0a763, __VMLINUX_SYMBOL_STR(_raw_spin_unlock) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x166ec38b, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xd79b5a02, __VMLINUX_SYMBOL_STR(allow_signal) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "6F83262A8BC2AF262164733");
