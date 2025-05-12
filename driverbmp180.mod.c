#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x92997ed8, "_printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x36948ecd, "i2c_register_driver" },
	{ 0x7482d442, "i2c_smbus_write_byte_data" },
	{ 0xf9a482f9, "msleep" },
	{ 0xfbc38a77, "i2c_smbus_read_byte_data" },
	{ 0xec85562e, "i2c_del_driver" },
	{ 0xc84d16dc, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("i2c:bmp180");

MODULE_INFO(srcversion, "3A1689F5AEA6A3C8FB93E52");
