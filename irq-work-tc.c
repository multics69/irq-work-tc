#include <linux/init.h>
#include <linux/module.h>
#include <linux/irq_work.h>
#include <linux/printk.h>

struct irq_work test_work;
int test_work_run; 

static void test_case(struct irq_work *work)
{
	test_work_run = 1;
}
 
static int __init irq_work_tc_init(void) 
{
	unsigned long flags;
	
	pr_info("before init: test_work_run: %d\n", test_work_run); 
	
	init_irq_work(&test_work, test_case);
	
	local_irq_save(flags);
	irq_work_queue(&test_work);
	local_irq_restore(flags);
	
	WARN_ON(irq_work_is_busy(&test_work));
	
	pr_info("after init: test_work_run: %d\n", test_work_run); 
	return 0; 
} 
 
static void __exit irq_work_tc_exit(void) 
{ 
	pr_info("at exit: test_work_run: %d\n", test_work_run); 
} 
 
module_init(irq_work_tc_init); 
module_exit(irq_work_tc_exit); 
 
MODULE_LICENSE("GPL");
