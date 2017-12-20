/*
** Adapted from an osek generated file, do not modify **

  Generic kernel config for a single periodic task:

  name: UsrTask
  offset: UsrTask_OFFSET (ms)
  period: UsrTask_PERIOD (ms)

 */
#include "osek_kernel.h"
#include "kernel_id.h"
#include "alarm.h"
#include "interrupt.h"
#include "resource.h"
#include "task.h"

#include "periods.h"

#define __STK_UNIT VP
#define __TCOUNT_STK_UNIT(sz) (((sz) + sizeof(__STK_UNIT) - 1) / sizeof(__STK_UNIT))

#define TNUM_ALARM     1
#define TNUM_COUNTER   1
#define TNUM_ISR2      0
#define TNUM_RESOURCE  0
#define TNUM_TASK      1
#define TNUM_EXTTASK   0

const UINT8 tnum_alarm    = TNUM_ALARM;
const UINT8 tnum_counter  = TNUM_COUNTER;
const UINT8 tnum_isr2     = TNUM_ISR2;
const UINT8 tnum_resource = TNUM_RESOURCE;
const UINT8 tnum_task     = TNUM_TASK;
const UINT8 tnum_exttask  = TNUM_EXTTASK;

 /****** Object OS ******/

 /****** Object TASK ******/

const TaskType UsrTask = 0;

extern void TASKNAME( UsrTask )( void );

static __STK_UNIT _stack_UsrTask[__TCOUNT_STK_UNIT(512)];

const Priority tinib_inipri[TNUM_TASK] = { TPRI_MINTASK + 1, };
const Priority tinib_exepri[TNUM_TASK] = { TPRI_MINTASK + 1, };
const UINT8 tinib_maxact[TNUM_TASK] = { (1) - 1, };
const AppModeType tinib_autoact[TNUM_TASK] = { 0x00000000, };
const FP tinib_task[TNUM_TASK] = { TASKNAME( UsrTask ), };
const __STK_UNIT tinib_stk[TNUM_TASK] = { (__STK_UNIT)_stack_UsrTask, };
const UINT16 tinib_stksz[TNUM_TASK] = { 512, };

TaskType tcb_next[TNUM_TASK];
UINT8 tcb_tstat[TNUM_TASK];
Priority tcb_curpri[TNUM_TASK];
UINT8 tcb_actcnt[TNUM_TASK];
EventMaskType tcb_curevt[TNUM_EXTTASK+1];
EventMaskType tcb_waievt[TNUM_EXTTASK+1];
ResourceType tcb_lastres[TNUM_TASK];
DEFINE_CTXB(TNUM_TASK);

 /****** Object COUNTER ******/

const CounterType SysTimerCnt = 0;

const TickType cntinib_maxval[TNUM_COUNTER] = { 10000, };
const TickType cntinib_maxval2[TNUM_COUNTER] = { 20001, };
const TickType cntinib_tickbase[TNUM_COUNTER] = { 1, };
const TickType cntinib_mincyc[TNUM_COUNTER] = { 1, };

AlarmType cntcb_almque[TNUM_COUNTER];
TickType cntcb_curval[TNUM_COUNTER];

 /****** Object ALARM ******/

const AlarmType cyclic_alarm = 0;

DeclareTask(UsrTask);
static void _activate_alarm_cyclic_alarm( void );
static void _activate_alarm_cyclic_alarm( void )
{ (void)ActivateTask( UsrTask ); }

const CounterType alminib_cntid[TNUM_ALARM] = { 0, };
const FP alminib_cback[TNUM_ALARM] = { _activate_alarm_cyclic_alarm, };
const AppModeType alminib_autosta[TNUM_ALARM] = { 0x00000001, };

const TickType alminib_almval[TNUM_ALARM] = { UsrTask_OFFSET, };
const TickType alminib_cycle[TNUM_ALARM] = { UsrTask_PERIOD, };

AlarmType almcb_next[TNUM_ALARM];
AlarmType almcb_prev[TNUM_ALARM];
TickType almcb_almval[TNUM_ALARM];
TickType almcb_cycle[TNUM_ALARM];

 /****** Object RESOURCE ******/


const Priority resinib_ceilpri[TNUM_RESOURCE+1] = { 0};

Priority rescb_prevpri[TNUM_RESOURCE+1];
ResourceType rescb_prevres[TNUM_RESOURCE+1];

 /****** Object EVENT ******/


 /****** Object ISR ******/


#define IPL_MAXISR2 0
const IPL ipl_maxisr2 = IPL_MAXISR2;


const Priority isrinib_intpri[TNUM_ISR2+1] = { 0};
ResourceType isrcb_lastres[TNUM_ISR2+1];

 /****** Object APPMODE ******/

void object_initialize( void )
{
	alarm_initialize();
	task_initialize();
}
