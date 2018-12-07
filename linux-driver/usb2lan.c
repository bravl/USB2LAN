#include <linux/usb.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hid.h>

static int usb_u2l_probe(struct usb_interface *iface,
		const struct usb_device_id *id)
{
	return 0;
}

static void usb_u2l_disconnect(struct usb_interface *iface)
{
}

static struct usb_device_id usb2lan_id_table[] = {
	{USB_DEVICE(0xfbce, 0x0001)},
	{}
};

MODULE_DEVICE_TABLE(usb, usb2lan_id_table);

static struct usb_driver usb_u2l_driver = {
	.name = "usb-u2l",
	.probe = usb_u2l_probe,
	.disconnect = usb_u2l_disconnect,
	.id_table = usb2lan_id_table,
};

MODULE_AUTHOR("Bram Vlerick");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("USB2LAN STM32F7 Driver");
MODULE_VERSION("0.1");
