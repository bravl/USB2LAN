/* General Includes*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/* USB Device Includes */
#include <linux/usb.h>
#include <linux/hid.h>

/* Network device includes */
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

struct usb2lan_device {
	struct usb_device *udev;
	struct net_device *ndev;
};

static int usb2lan_net_open(struct net_device *ndev)
{
	return 0;
}

static int usb2lan_net_close(struct net_device *ndev)
{
	return 0;	
}

static int usb2lan_net_ioctl(struct net_device *ndev, struct ifreq *ifr, int cmd)
{
	return 0;
}

static const struct net_device_ops usb2lan_netdev_ops = {
	.ndo_open = usb2lan_net_open,
	.ndo_stop = usb2lan_net_close,
	.ndo_do_ioctl = usb2lan_net_ioctl,
};

static int usb_u2l_probe(struct usb_interface *iface,
		const struct usb_device_id *id)
{
	int retval = -ENOMEM;
	struct usb2lan_device *dev = NULL;
	struct usb_device *udev = interface_to_usbdev(iface);
	struct net_device *ndev = alloc_etherdev(sizeof(struct usb2lan_device));
	if (!ndev) goto err;

	dev_info(&iface->dev,"Probing USB2LAN module\n");

	dev = netdev_priv(ndev);	
	SET_NETDEV_DEV(ndev, &iface->dev);
	ndev->netdev_ops = &usb2lan_netdev_ops;

	dev->udev = usb_get_dev(udev);
	usb_set_intfdata(iface, dev);
	dev->ndev = ndev;
	

	register_netdev(ndev);

	dev_info(&iface->dev, "USB2LAN Device attached\n");

	return 0;
err:
	dev_err(&iface->dev, "USB2LAN Probe failed\n");
	return retval;
}

static void usb_u2l_disconnect(struct usb_interface *iface)
{
	struct usb2lan_device *dev = usb_get_intfdata(iface);

	dev_info(&iface->dev,"Disconnecting USB2LAN module\n");
	unregister_netdev(dev->ndev);
	free_netdev(dev->ndev);
	usb_set_intfdata(iface,NULL);
	usb_put_dev(dev->udev);
	kfree(dev);
	
	dev_info(&iface->dev,"Disconnected USB2LAN Device\n");
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

module_usb_driver(usb_u2l_driver);

MODULE_AUTHOR("Bram Vlerick");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("USB2LAN STM32F7 Driver");
MODULE_VERSION("0.1");
