#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <linux/rtc.h>
#include <linux/bcd.h>
#include <linux/mutex.h>
#include <linux/workqueue.h>

static unsigned short ignore[] = { I2C_CLIENT_END };
static unsigned short normal_addr[] = { I2C_CLIENT_END, I2C_CLIENT_END };
static struct i2c_client_address_data addr_data = {
	.normal_i2c	= normal_addr,
	.probe		= ignore,
	.ignore		= ignore,
};
static int  at24cxx_detect(struct i2c_adapter *adapter, int address, int kind)
{
       printK("at24cxx_detect");
	return 0;   	
}
static int at24cxx_attach(struct i2c_adapter *adapter)
{
	return i2c_probe(adapter, &addr_data, at24cxx_detect);
}

static int  at24cxx_detach(struct i2c_client *client)
{
	printK("at24cxx_detach");
	return 0;
}

/*1 分配一个i2c结构体*/
/*2设置一个i2c_driver结构体*/

static struct i2c_driver at24cxx_driver = {
	.driver = {
		.name	=  "at24cxx",
	},
	.attach_adapter = at24cxx_attach,
	.detach_client = at24cxx_detach,
};

static int at24cxx_init(void)
{
     i2c_add_driver(&at24cxx_driver);
     return 0;
}

static void at24cxx_exit(void)
{
     i2c_del_driver(&at24cxx_driver);
}

module_init(at24cxx_init);
module_exit(at24cxx_exit);
MODULE_LICENSE("GPL");
