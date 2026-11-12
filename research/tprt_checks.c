
// debuggable_check @ 1bbed8 : NO FUNCTION, creating

// ===== debuggable_check -> func FUN_001bbed8 @ 001bbed8 =====

void FUN_001bbed8(undefined8 param_1,long param_2)

{
  undefined8 uVar1;
  undefined *extraout_x8;
  undefined *puVar2;
  int iVar3;
  int unaff_w19;
  int unaff_w20;
  long unaff_x21;
  long unaff_x22;
  long unaff_x23;
  long unaff_x24;
  int unaff_w26;
  int unaff_w28;
  long unaff_x29;
  undefined8 uStack0000000000000030;
  
  uVar1 = func_0x001f71d8(param_1,param_2 + 0xec2);
  func_0x00162b6c(&uStack0000000000000030,uVar1);
  *(undefined8 *)(unaff_x29 + -0x60) = uStack0000000000000030;
  iVar3 = -0x5054a03d;
  puVar2 = extraout_x8;
  do {
    while( true ) {
      while (iVar3 < unaff_w26) {
        if (iVar3 == unaff_w28) {
          iVar3 = unaff_w26;
          if (*(long *)(unaff_x29 + -0x60) != 0) {
            iVar3 = unaff_w19;
          }
          puVar2 = &UNK_0021ff95;
        }
      }
      if (iVar3 < unaff_w19) break;
      if (iVar3 == unaff_w19) {
        puVar2 = *(undefined **)(unaff_x29 + -0x60);
        iVar3 = -0x157cda2;
      }
    }
  } while (iVar3 != unaff_w26);
  iVar3 = 0x521c3edc;
  if (puVar2 != (undefined *)0x0) {
    iVar3 = 0x7d346b4c;
  }
  if (unaff_w20 <= iVar3) {
    unaff_x21 = unaff_x23;
  }
                    /* WARNING: Could not recover jumptable at 0x001bb328. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(*(long *)(unaff_x24 + unaff_x21) + unaff_x22))();
  return;
}



// zip_verify_data @ 1ecde8 : NO FUNCTION, creating

// ===== zip_verify_data -> func FUN_001ecde8 @ 001ecde8 =====

undefined8 FUN_001ecde8(void)

{
  undefined8 uVar1;
  uint *in_x9;
  long unaff_x21;
  
  if (*in_x9 < 0xe) {
                    /* WARNING: Could not recover jumptable at 0x001ece0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*(code *)(&UNK_001ece10 + (ulong)*(byte *)(unaff_x21 + (ulong)*in_x9) * 4))
                      (0xfffffffd,1);
    return uVar1;
  }
  return 0xfffffffe;
}



// zip_verify_hdr @ 1ecf44 : NO FUNCTION, creating

// ===== zip_verify_hdr -> func FUN_001ecf44 @ 001ecf44 =====

undefined8 FUN_001ecf44(long param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  long in_x9;
  long unaff_x19;
  undefined4 unaff_w20;
  long unaff_x21;
  undefined4 unaff_w24;
  
  *(long *)(unaff_x19 + 0x30) = param_1 + 0x2ae;
  *(undefined4 *)(in_x9 + 8) = unaff_w24;
  if (**(uint **)(unaff_x19 + 0x38) < 0xe) {
                    /* WARNING: Could not recover jumptable at 0x001ece0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*(code *)(&UNK_001ece10 +
                      (ulong)*(byte *)(unaff_x21 + (ulong)**(uint **)(unaff_x19 + 0x38)) * 4))
                      (0xfffffffd,1,param_3,unaff_w20);
    return uVar1;
  }
  return 0xfffffffe;
}



// zip_parse @ 1ef8ac : NO FUNCTION, creating

// ===== zip_parse -> func FUN_001ef8ac @ 001ef8ac =====

uint FUN_001ef8ac(void)

{
  uint uVar1;
  uint uVar2;
  long unaff_x19;
  uint unaff_w20;
  long unaff_x21;
  
  uVar2 = func_0x0015df60(unaff_x21 + 0x54a);
  if ((unaff_x19 != 0) && (unaff_w20 != 0)) {
    uVar1 = unaff_w20 - 1;
    if (uVar2 + 1 <= unaff_w20) {
      uVar1 = uVar2;
    }
    func_0x0015dd80();
    *(undefined1 *)(unaff_x19 + (ulong)uVar1) = 0;
  }
  return uVar2;
}



// magisk_check @ 1f15d8 : NO FUNCTION, creating

// ===== magisk_check -> func FUN_001f15d8 @ 001f15d8 =====

bool FUN_001f15d8(long param_1)

{
  int iVar1;
  
  iVar1 = func_0x0015dbf0(param_1 + 0x1fe,0);
  if (iVar1 == 0) {
    func_0x001f5d58();
  }
  return iVar1 == 0;
}

