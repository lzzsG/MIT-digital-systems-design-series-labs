/*
 * Generated by Bluespec Compiler, version 2023.07 (build 0eb551d)
 * 
 * On Tue Apr 23 02:39:09 CST 2024
 * 
 */

/* Generation options: */
#ifndef __mkTest_h__
#define __mkTest_h__

#include "bluesim_types.h"
#include "bs_module.h"
#include "bluesim_primitives.h"
#include "bs_vcd.h"


/* Class declaration for the mkTest module */
class MOD_mkTest : public Module {
 
 /* Clock handles */
 private:
  tClock __clk_handle_0;
 
 /* Clock gate handles */
 public:
  tUInt8 *clk_gate[0];
 
 /* Instantiation parameters */
 public:
 
 /* Module state */
 public:
  MOD_Reg<tUInt32> INST_ctr_fsm;
  MOD_Reg<tUInt8> INST_going;
  MOD_Wire<tUInt8> INST_test_fsm_abort;
  MOD_Reg<tUInt8> INST_test_fsm_start_reg;
  MOD_Reg<tUInt8> INST_test_fsm_start_reg_1;
  MOD_Wire<tUInt8> INST_test_fsm_start_reg_2;
  MOD_Wire<tUInt8> INST_test_fsm_start_wire;
  MOD_Reg<tUInt8> INST_test_fsm_state_can_overlap;
  MOD_Reg<tUInt8> INST_test_fsm_state_fired;
  MOD_Wire<tUInt8> INST_test_fsm_state_fired_1;
  MOD_ConfigReg<tUInt8> INST_test_fsm_state_mkFSMstate;
  MOD_Wire<tUInt8> INST_test_fsm_state_overlap_pw;
  MOD_Wire<tUInt8> INST_test_fsm_state_set_pw;
  MOD_RegFile<tUInt8,tUWide> INST_tests;
  MOD_Reg<tUInt8> INST_verbose;
 
 /* Constructor */
 public:
  MOD_mkTest(tSimStateHdl simHdl, char const *name, Module *parent);
 
 /* Symbol init methods */
 private:
  void init_symbols_0();
 
 /* Reset signal definitions */
 private:
  tUInt8 PORT_RST_N;
 
 /* Port definitions */
 public:
 
 /* Publicly accessible definitions */
 public:
  tUInt8 DEF_WILL_FIRE_RL_test_fsm_action_l30c9;
  tUInt8 DEF_WILL_FIRE_RL_test_fsm_action_l17c13;
  tUInt8 DEF_WILL_FIRE_RL_test_fsm_action_l13c10;
  tUInt32 DEF_x__h13440;
 
 /* Local definitions */
 private:
  tUWide DEF_tests_sub_ctr_fsm_7_BITS_3_TO_0_5___d46;
 
 /* Rules */
 public:
  void RL_test_fsm_start_reg__dreg_update();
  void RL_test_fsm_state_handle_abort();
  void RL_test_fsm_state_fired__dreg_update();
  void RL_test_fsm_state_every();
  void RL_test_fsm_restart();
  void RL_test_fsm_action_l13c10();
  void RL_test_fsm_action_l17c13();
  void RL_test_fsm_action_l30c9();
  void RL_test_fsm_idle_l12c7();
  void RL_test_fsm_fsm_start();
  void RL_start();
  void __me_check_5();
  void __me_check_6();
 
 /* Methods */
 public:
 
 /* Reset routines */
 public:
  void reset_RST_N(tUInt8 ARG_rst_in);
 
 /* Static handles to reset routines */
 public:
 
 /* Pointers to reset fns in parent module for asserting output resets */
 private:
 
 /* Functions for the parent module to register its reset fns */
 public:
 
 /* Functions to set the elaborated clock id */
 public:
  void set_clk_0(char const *s);
 
 /* State dumping routine */
 public:
  void dump_state(unsigned int indent);
 
 /* VCD dumping routines */
 public:
  unsigned int dump_VCD_defs(unsigned int levels);
  void dump_VCD(tVCDDumpType dt, unsigned int levels, MOD_mkTest &backing);
  void vcd_defs(tVCDDumpType dt, MOD_mkTest &backing);
  void vcd_prims(tVCDDumpType dt, MOD_mkTest &backing);
};

#endif /* ifndef __mkTest_h__ */
