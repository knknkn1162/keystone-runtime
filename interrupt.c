#include "regs.h"
#include "sbi.h"
#include "timex.h"
#include "interrupt.h"

#define DEFAULT_CLOCK_DELAY 40000

void init_timer(void)
{
  sbi_set_timer(get_cycles64() + DEFAULT_CLOCK_DELAY);
}

void handle_timer_interrupt()
{
  sbi_set_timer(get_cycles64() + DEFAULT_CLOCK_DELAY);
  return;
}

void handle_interrupts(struct encl_ctx_t* regs)
{
  unsigned long cause = regs->scause;

  switch(cause) {
    case INTERRUPT_CAUSE_TIMER:
      handle_timer_interrupt();
      break;
    /* ignore other interrupts */
    case INTERRUPT_CAUSE_SOFTWARE:
    case INTERRUPT_CAUSE_EXTERNAL:
    default:
      return;
  }
}
