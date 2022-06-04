#include "cpu/exec.h"

make_EHelper(test) {//test指令
  rtl_and(&t2, &id_dest->val, &id_src->val);
  rtl_update_ZFSF(&t2, id_dest->width);
  rtl_set_CF(&tzero);
  rtl_set_OF(&tzero);
  print_asm_template2(test);
}

make_EHelper(and) {//and指令
	rtl_and(&t2, &id_dest->val, &id_src->val);
    operand_write(id_dest, &t2);
	rtl_update_ZFSF(&t2, id_dest->width);
	rtl_set_CF(&tzero);
	rtl_set_OF(&tzero);
    print_asm_template2(and);
}

make_EHelper(xor) {//xor指令定义
    rtl_xor(&t2, &id_dest->val, &id_src->val);
	operand_write(id_dest, &t2);
	rtl_update_ZFSF(&t2, id_dest->width);
	rtl_set_CF(&tzero);
	rtl_set_OF(&tzero);
    print_asm_template2(xor);
}

make_EHelper(or) {//or指令
	rtl_or(&t2, &id_dest->val, &id_src->val);
	operand_write(id_dest, &t2);
	rtl_set_OF(&tzero);
	rtl_set_CF(&tzero);
	rtl_update_ZFSF(&t2, id_dest->width);
    print_asm_template2(or);
}

make_EHelper(sar) {
  // unnecessary to update CF and OF in NEMU
	if (id_dest->width == 1)
		id_dest->val = (int8_t)id_dest->val;
	else if (id_dest->width == 2)
		id_dest->val = (int16_t)id_dest->val;
	rtl_sar(&t2, &id_dest->val, &id_src->val);
	operand_write(id_dest, &t2);
	rtl_update_ZFSF(&t2, id_dest->width);
    print_asm_template2(sar);
}

make_EHelper(shl) {
  // unnecessary to update CF and OF in NEMU
	rtl_shl(&t2, &id_dest->val, &id_src->val);
	operand_write(id_dest, &t2);
	rtl_update_ZFSF(&t2, id_dest->width);
  print_asm_template2(shl);
}

make_EHelper(shr) {
  // unnecessary to update CF and OF in NEMU
	rtl_shr(&t2, &id_dest->val, &id_src->val);
	operand_write(id_dest, &t2);
	rtl_update_ZFSF(&t2, id_dest->width);
  print_asm_template2(shr);
}

make_EHelper(setcc) {
  uint8_t subcode = decoding.opcode & 0xf;
  rtl_setcc(&t2, subcode);
  operand_write(id_dest, &t2);

  print_asm("set%s %s", get_cc_name(subcode), id_dest->str);
}

make_EHelper(not) {//not指令
  rtl_not(&id_dest->val);
  operand_write(id_dest, &id_dest->val);
  print_asm_template1(not);
}
