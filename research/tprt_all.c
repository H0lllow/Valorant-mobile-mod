
// ===== entry @ 0015e0f0 =====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  _DAT_0025e2f8 = func_0x001de9ec(0);
  uRam000000000025e300 = func_0x001df8cc(0xd);
  puRam000000000025e308 = &UNK_0015e1e8;
  return;
}


// ===== _INIT_1 @ 0015e130 =====

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Switch with 1 destination removed at 0x0015e0bc */

void _INIT_1(void)

{
  lRam000000000025e340 = func_0x0015de70(0x400);
  lRam000000000025e348 = lRam000000000025e340;
  lRam000000000025e350 = lRam000000000025e340 + 0x400;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== _INIT_2 @ 0015e170 =====

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Switch with 1 destination removed at 0x0015e0bc */

void _INIT_2(void)

{
  func_0x001f1cf4(0x25e390);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== _FINI_1 @ 0015e1ac =====

void _FINI_1(void)

{
  (*(code *)PTR___cxa_finalize_0023fb98)(&DAT_0023e790);
  return;
}


// ===== _FINI_0 @ 0015e1bc =====

void _FINI_0(void)

{
  return;
}


// ===== JNI_OnLoad @ 0015e388 =====

undefined4 JNI_OnLoad(long *param_1)

{
  undefined8 uVar1;
  int iVar2;
  int iVar3;
  undefined4 unaff_w20;
  long lStack_80;
  long *plStack_78;
  int iStack_6c;
  long lStack_68;
  
  plStack_78 = &lStack_80;
  lStack_80 = 0;
  iStack_6c = (**(code **)(*param_1 + 0x30))(param_1,&lStack_80,0x10004);
  iVar3 = 0x22f0693f;
code_r0x0015e46c:
  do {
    uVar1 = 0xf0;
    if (0x44b82854 < iVar3) {
      uVar1 = 0x20;
    }
    switch(uVar1) {
    case 0:
code_r0x0015e77c:
      return unaff_w20;
    case 0x10:
code_r0x0015e4f0:
      uVar1 = 0x120;
      if (iVar3 != 0x44b82855) {
        uVar1 = 0x108;
      }
      switch(uVar1) {
      case 0:
        goto code_r0x0015e77c;
      default:
        break;
      case 0x10:
        goto code_r0x0015e4f0;
      case 0x20:
code_r0x0015e4c8:
        uVar1 = 200;
        if (0x5d7b4e59 < iVar3) {
          uVar1 = 0x128;
        }
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
        switch(uVar1) {
        case 0:
          goto code_r0x0015e77c;
        default:
          break;
        case 0x10:
          goto code_r0x0015e4f0;
        case 0x18:
          goto code_r0x0015e6dc;
        case 0x20:
          goto code_r0x0015e4c8;
        case 0x28:
          goto code_r0x0015e6c0;
        case 0x38:
code_r0x0015e5ec:
          uVar1 = 0x48;
          if (iVar3 != -0xf84ebb9) {
            uVar1 = 0x90;
          }
          switch(uVar1) {
          case 0:
            goto code_r0x0015e77c;
          default:
            break;
          case 0x10:
            goto code_r0x0015e4f0;
          case 0x18:
            goto code_r0x0015e6dc;
          case 0x20:
            goto code_r0x0015e4c8;
          case 0x28:
            goto code_r0x0015e6c0;
          case 0x38:
            goto code_r0x0015e5ec;
          case 0x40:
            goto code_r0x0015e664;
          case 0x48:
            goto code_r0x0015e608;
          case 0x50:
            goto code_r0x0015e6b0;
          case 0x58:
code_r0x0015e5cc:
            uVar1 = 0xd0;
            if (iVar3 != 0x5d7b4e5a) {
              uVar1 = 0x30;
            }
            switch(uVar1) {
            case 0:
              goto code_r0x0015e77c;
            case 0x10:
              goto code_r0x0015e4f0;
            case 0x20:
              goto code_r0x0015e4c8;
            default:
              break;
            case 0x40:
              goto code_r0x0015e664;
            case 0x50:
              goto code_r0x0015e6b0;
            case 0x60:
code_r0x0015e578:
              uVar1 = 0xc0;
              if (0x30fae710 < iVar3) {
                uVar1 = 0x78;
              }
              switch(uVar1) {
              case 0:
                goto code_r0x0015e77c;
              default:
                break;
              case 0x10:
                goto code_r0x0015e4f0;
              case 0x18:
                goto code_r0x0015e6dc;
              case 0x20:
                goto code_r0x0015e4c8;
              case 0x28:
                goto code_r0x0015e6c0;
              case 0x38:
                goto code_r0x0015e5ec;
              case 0x40:
                goto code_r0x0015e664;
              case 0x48:
                goto code_r0x0015e608;
              case 0x50:
                goto code_r0x0015e6b0;
              case 0x58:
                goto code_r0x0015e5cc;
              case 0x60:
                goto code_r0x0015e578;
              case 0x78:
code_r0x0015e62c:
                uVar1 = 0xe8;
                if (0x3b21f14f < iVar3) {
                  uVar1 = 0x28;
                }
                switch(uVar1) {
                case 0:
                  goto code_r0x0015e77c;
                default:
                  break;
                case 0x10:
                  goto code_r0x0015e4f0;
                case 0x18:
                  goto code_r0x0015e6dc;
                case 0x20:
                  goto code_r0x0015e4c8;
                case 0x28:
                  goto code_r0x0015e6c0;
                case 0x38:
                  goto code_r0x0015e5ec;
                case 0x40:
                  goto code_r0x0015e664;
                case 0x48:
                  goto code_r0x0015e608;
                case 0x50:
                  goto code_r0x0015e6b0;
                case 0x58:
                  goto code_r0x0015e5cc;
                case 0x60:
                  goto code_r0x0015e578;
                case 0x78:
                  goto code_r0x0015e62c;
                case 0x80:
code_r0x0015e694:
                  uVar1 = 0x50;
                  if (iVar3 != 0x6e142ec8) {
                    uVar1 = 0xb8;
                  }
                  switch(uVar1) {
                  case 0:
                    goto code_r0x0015e77c;
                  default:
                    break;
                  case 0x10:
                    goto code_r0x0015e4f0;
                  case 0x18:
                    goto code_r0x0015e6dc;
                  case 0x20:
                    goto code_r0x0015e4c8;
                  case 0x28:
                    goto code_r0x0015e6c0;
                  case 0x38:
                    goto code_r0x0015e5ec;
                  case 0x40:
                    goto code_r0x0015e664;
                  case 0x48:
                    goto code_r0x0015e608;
                  case 0x50:
                    goto code_r0x0015e6b0;
                  case 0x58:
                    goto code_r0x0015e5cc;
                  case 0x60:
                    goto code_r0x0015e578;
                  case 0x78:
                    goto code_r0x0015e62c;
                  case 0x80:
                    goto code_r0x0015e694;
                  case 0x88:
code_r0x0015e60c:
                    uVar1 = 0xd8;
                    if (iVar3 != 0x5ad22f2f) {
                      uVar1 = 0x110;
                    }
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
                    switch(uVar1) {
                    case 0:
                      goto code_r0x0015e77c;
                    default:
                      break;
                    case 0x10:
                      goto code_r0x0015e4f0;
                    case 0x18:
                      goto code_r0x0015e6dc;
                    case 0x20:
                      goto code_r0x0015e4c8;
                    case 0x28:
                      goto code_r0x0015e6c0;
                    case 0x38:
                      goto code_r0x0015e5ec;
                    case 0x40:
                      goto code_r0x0015e664;
                    case 0x48:
                      goto code_r0x0015e608;
                    case 0x50:
                      goto code_r0x0015e6b0;
                    case 0x58:
                      goto code_r0x0015e5cc;
                    case 0x60:
                      goto code_r0x0015e578;
                    case 0x78:
                      goto code_r0x0015e62c;
                    case 0x80:
                      goto code_r0x0015e694;
                    case 0x88:
                      goto code_r0x0015e60c;
                    case 0xa0:
code_r0x0015e494:
                      uVar1 = 0x100;
                      if (-0xf84ebba < iVar3) {
                        uVar1 = 0x38;
                      }
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
                      switch(uVar1) {
                      case 0:
                        goto code_r0x0015e77c;
                      default:
                        break;
                      case 0x10:
                        goto code_r0x0015e4f0;
                      case 0x18:
                        goto code_r0x0015e6dc;
                      case 0x20:
                        goto code_r0x0015e4c8;
                      case 0x28:
                        goto code_r0x0015e6c0;
                      case 0x38:
                        goto code_r0x0015e5ec;
                      case 0x40:
                        goto code_r0x0015e664;
                      case 0x48:
                        goto code_r0x0015e608;
                      case 0x50:
                        goto code_r0x0015e6b0;
                      case 0x58:
                        goto code_r0x0015e5cc;
                      case 0x60:
                        goto code_r0x0015e578;
                      case 0x78:
                        goto code_r0x0015e62c;
                      case 0x80:
                        goto code_r0x0015e694;
                      case 0x88:
                        goto code_r0x0015e60c;
                      case 0xa0:
                        goto code_r0x0015e494;
                      case 0xa8:
code_r0x0015e748:
                        uVar1 = 0xf8;
                        if (iVar3 != 0x6e221a17) {
                          uVar1 = 0x98;
                        }
                        switch(uVar1) {
                        case 0:
                          goto code_r0x0015e77c;
                        default:
                          break;
                        case 0x10:
                          goto code_r0x0015e4f0;
                        case 0x18:
                          goto code_r0x0015e6dc;
                        case 0x20:
                          goto code_r0x0015e4c8;
                        case 0x28:
                          goto code_r0x0015e6c0;
                        case 0x38:
                          goto code_r0x0015e5ec;
                        case 0x40:
                          goto code_r0x0015e664;
                        case 0x48:
                          goto code_r0x0015e608;
                        case 0x50:
                          goto code_r0x0015e6b0;
                        case 0x58:
                          goto code_r0x0015e5cc;
                        case 0x60:
                          goto code_r0x0015e578;
                        case 0x78:
                          goto code_r0x0015e62c;
                        case 0x80:
                          goto code_r0x0015e694;
                        case 0x88:
                          goto code_r0x0015e60c;
                        case 0xa0:
                          goto code_r0x0015e494;
                        case 0xa8:
                          goto code_r0x0015e748;
                        case 0xb0:
code_r0x0015e678:
                          uVar1 = 0x80;
                          if (0x6e221a16 < iVar3) {
                            uVar1 = 0xa8;
                          }
                          switch(uVar1) {
                          case 0:
                            goto code_r0x0015e77c;
                          default:
                            break;
                          case 0x10:
                            goto code_r0x0015e4f0;
                          case 0x18:
                            goto code_r0x0015e6dc;
                          case 0x20:
                            goto code_r0x0015e4c8;
                          case 0x28:
                            goto code_r0x0015e6c0;
                          case 0x38:
                            goto code_r0x0015e5ec;
                          case 0x40:
                            goto code_r0x0015e664;
                          case 0x48:
                            goto code_r0x0015e608;
                          case 0x50:
                            goto code_r0x0015e6b0;
                          case 0x58:
                            goto code_r0x0015e5cc;
                          case 0x60:
                            goto code_r0x0015e578;
                          case 0x78:
                            goto code_r0x0015e62c;
                          case 0x80:
                            goto code_r0x0015e694;
                          case 0x88:
                            goto code_r0x0015e60c;
                          case 0xa0:
                            goto code_r0x0015e494;
                          case 0xa8:
                            goto code_r0x0015e748;
                          }
                        case 0xc0:
code_r0x0015e58c:
                          uVar1 = 0xe0;
                          if (iVar3 != 0x22f0693f) {
                            uVar1 = 0x118;
                          }
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
                          switch(uVar1) {
                          case 0:
                            goto code_r0x0015e77c;
                          default:
                            break;
                          case 0x10:
                            goto code_r0x0015e4f0;
                          case 0x18:
                            goto code_r0x0015e6dc;
                          case 0x20:
                            goto code_r0x0015e4c8;
                          case 0x28:
                            goto code_r0x0015e6c0;
                          case 0x38:
                            goto code_r0x0015e5ec;
                          case 0x40:
                            goto code_r0x0015e664;
                          case 0x48:
                            goto code_r0x0015e608;
                          case 0x50:
                            goto code_r0x0015e6b0;
                          case 0x58:
                            goto code_r0x0015e5cc;
                          case 0x60:
                            goto code_r0x0015e578;
                          case 0x78:
                            goto code_r0x0015e62c;
                          case 0x80:
                            goto code_r0x0015e694;
                          case 0x88:
                            goto code_r0x0015e60c;
                          case 0xa0:
                            goto code_r0x0015e494;
                          case 0xa8:
                            goto code_r0x0015e748;
                          case 0xb0:
                            goto code_r0x0015e678;
                          case 0xc0:
                            goto code_r0x0015e58c;
                          case 200:
                            goto code_r0x0015e4dc;
                          case 0xd0:
                            goto code_r0x0015e5e8;
                          case 0xd8:
                            goto code_r0x0015e628;
                          case 0xe0:
                            goto code_r0x0015e5a8;
                          case 0xe8:
                            goto code_r0x0015e648;
                          case 0xf0:
code_r0x0015e480:
                            uVar1 = 0xa0;
                            if (0x22f0693e < iVar3) {
                              uVar1 = 0x60;
                            }
                            switch(uVar1) {
                            case 0:
                              goto code_r0x0015e77c;
                            case 0x20:
                              goto code_r0x0015e4c8;
                            case 0x40:
                              goto code_r0x0015e664;
                            case 0x60:
                              goto code_r0x0015e578;
                            case 0x80:
                              goto code_r0x0015e694;
                            case 0xa0:
                              goto code_r0x0015e494;
                            case 0xe0:
                              goto code_r0x0015e5a8;
                            }
                            goto code_r0x0015e58c;
                          case 0xf8:
                            goto code_r0x0015e764;
                          case 0x100:
                            goto code_r0x0015e4a8;
                          case 0x120:
                            goto code_r0x0015e50c;
                          case 0x128:
code_r0x0015e5b8:
                            uVar1 = 0x58;
                            if (0x6e142ec7 < iVar3) {
                              uVar1 = 0xb0;
                            }
                            switch(uVar1) {
                            case 0:
                              goto code_r0x0015e77c;
                            default:
                              break;
                            case 0x10:
                              goto code_r0x0015e4f0;
                            case 0x18:
                              goto code_r0x0015e6dc;
                            case 0x20:
                              goto code_r0x0015e4c8;
                            case 0x28:
                              goto code_r0x0015e6c0;
                            case 0x38:
                              goto code_r0x0015e5ec;
                            case 0x40:
                              goto code_r0x0015e664;
                            case 0x48:
                              goto code_r0x0015e608;
                            case 0x50:
                              goto code_r0x0015e6b0;
                            case 0x58:
                              goto code_r0x0015e5cc;
                            case 0x60:
                              goto code_r0x0015e578;
                            case 0x78:
                              goto code_r0x0015e62c;
                            case 0x80:
                              goto code_r0x0015e694;
                            case 0x88:
                              goto code_r0x0015e60c;
                            case 0xa0:
                              goto code_r0x0015e494;
                            case 0xa8:
                              goto code_r0x0015e748;
                            case 0xb0:
                              goto code_r0x0015e678;
                            case 0xc0:
                              goto code_r0x0015e58c;
                            case 200:
                              goto code_r0x0015e4dc;
                            case 0xd0:
                              goto code_r0x0015e5e8;
                            case 0xd8:
                              goto code_r0x0015e628;
                            case 0xe0:
                              goto code_r0x0015e5a8;
                            case 0xe8:
                              goto code_r0x0015e648;
                            case 0xf0:
                              goto code_r0x0015e480;
                            case 0xf8:
                              goto code_r0x0015e764;
                            }
                          }
                        case 200:
                          goto code_r0x0015e4dc;
                        case 0xd0:
                          goto code_r0x0015e5e8;
                        case 0xd8:
                          goto code_r0x0015e628;
                        case 0xe0:
                          goto code_r0x0015e5a8;
                        case 0xe8:
                          goto code_r0x0015e648;
                        case 0xf0:
                          goto code_r0x0015e480;
                        case 0xf8:
                          goto code_r0x0015e764;
                        }
                      case 0xb0:
                        goto code_r0x0015e678;
                      case 0xc0:
                        goto code_r0x0015e58c;
                      case 200:
                        goto code_r0x0015e4dc;
                      case 0xd0:
                        goto code_r0x0015e5e8;
                      case 0xd8:
                        goto code_r0x0015e628;
                      case 0xe0:
                        goto code_r0x0015e5a8;
                      case 0xe8:
                        goto code_r0x0015e648;
                      case 0xf0:
                        goto code_r0x0015e480;
                      case 0xf8:
                        goto code_r0x0015e764;
                      case 0x100:
                        goto code_r0x0015e4a8;
                      case 0x120:
                        goto code_r0x0015e50c;
                      case 0x128:
                        goto code_r0x0015e5b8;
                      }
                    case 0xa8:
                      goto code_r0x0015e748;
                    case 0xb0:
                      goto code_r0x0015e678;
                    case 0xc0:
                      goto code_r0x0015e58c;
                    case 200:
code_r0x0015e4dc:
                      uVar1 = 0x10;
                      if (0x5ad22f2e < iVar3) {
                        uVar1 = 0x88;
                      }
                      switch(uVar1) {
                      case 0:
                        goto code_r0x0015e77c;
                      default:
                        break;
                      case 0x10:
                        goto code_r0x0015e4f0;
                      case 0x18:
                        goto code_r0x0015e6dc;
                      case 0x20:
                        goto code_r0x0015e4c8;
                      case 0x28:
                        goto code_r0x0015e6c0;
                      case 0x38:
                        goto code_r0x0015e5ec;
                      case 0x40:
                        goto code_r0x0015e664;
                      case 0x48:
                        goto code_r0x0015e608;
                      case 0x50:
                        goto code_r0x0015e6b0;
                      case 0x58:
                        goto code_r0x0015e5cc;
                      case 0x60:
                        goto code_r0x0015e578;
                      case 0x78:
                        goto code_r0x0015e62c;
                      case 0x80:
                        goto code_r0x0015e694;
                      case 0x88:
                        goto code_r0x0015e60c;
                      }
                    case 0xd0:
                      goto code_r0x0015e5e8;
                    case 0xd8:
                      goto code_r0x0015e628;
                    case 0xe0:
                      goto code_r0x0015e5a8;
                    case 0xe8:
                      goto code_r0x0015e648;
                    case 0xf0:
                      goto code_r0x0015e480;
                    case 0xf8:
                      goto code_r0x0015e764;
                    case 0x100:
                      goto code_r0x0015e4a8;
                    case 0x120:
                      goto code_r0x0015e50c;
                    case 0x128:
                      goto code_r0x0015e5b8;
                    }
                  case 0xa0:
                    goto code_r0x0015e494;
                  case 0xa8:
                    goto code_r0x0015e748;
                  case 0xb0:
                    goto code_r0x0015e678;
                  case 0xc0:
                    goto code_r0x0015e58c;
                  case 200:
                    goto code_r0x0015e4dc;
                  case 0xd0:
                    goto code_r0x0015e5e8;
                  case 0xd8:
                    goto code_r0x0015e628;
                  case 0xe0:
                    goto code_r0x0015e5a8;
                  case 0xe8:
                    goto code_r0x0015e648;
                  case 0xf0:
                    goto code_r0x0015e480;
                  case 0xf8:
                    goto code_r0x0015e764;
                  }
                case 0x88:
                  goto code_r0x0015e60c;
                case 0xa0:
                  goto code_r0x0015e494;
                case 0xa8:
                  goto code_r0x0015e748;
                case 0xb0:
                  goto code_r0x0015e678;
                case 0xc0:
                  goto code_r0x0015e58c;
                case 200:
                  goto code_r0x0015e4dc;
                case 0xd0:
                  goto code_r0x0015e5e8;
                case 0xd8:
                  goto code_r0x0015e628;
                case 0xe0:
                  goto code_r0x0015e5a8;
                case 0xe8:
                  goto code_r0x0015e648;
                }
              case 0x80:
                goto code_r0x0015e694;
              case 0x88:
                goto code_r0x0015e60c;
              case 0xa0:
                goto code_r0x0015e494;
              case 0xa8:
                goto code_r0x0015e748;
              case 0xb0:
                goto code_r0x0015e678;
              case 0xc0:
                goto code_r0x0015e58c;
              case 200:
                goto code_r0x0015e4dc;
              case 0xd0:
                goto code_r0x0015e5e8;
              case 0xd8:
                goto code_r0x0015e628;
              case 0xe0:
                goto code_r0x0015e5a8;
              case 0xe8:
code_r0x0015e648:
                uVar1 = 0x40;
                if (iVar3 != 0x30fae711) {
                  uVar1 = 0x68;
                }
                switch(uVar1) {
                case 0:
                  goto code_r0x0015e77c;
                default:
                  break;
                case 0x10:
                  goto code_r0x0015e4f0;
                case 0x18:
                  goto code_r0x0015e6dc;
                case 0x20:
                  goto code_r0x0015e4c8;
                case 0x28:
                  goto code_r0x0015e6c0;
                case 0x38:
                  goto code_r0x0015e5ec;
                case 0x40:
                  goto code_r0x0015e664;
                case 0x48:
                  goto code_r0x0015e608;
                case 0x50:
                  goto code_r0x0015e6b0;
                case 0x58:
                  goto code_r0x0015e5cc;
                case 0x60:
                  goto code_r0x0015e578;
                }
              case 0xf0:
                goto code_r0x0015e480;
              case 0xf8:
                goto code_r0x0015e764;
              }
            case 0x80:
              goto code_r0x0015e694;
            case 0xa0:
              goto code_r0x0015e494;
            case 0xb0:
              goto code_r0x0015e678;
            case 0xc0:
              goto code_r0x0015e58c;
            case 0xd0:
              goto code_r0x0015e5e8;
            case 0xe0:
              goto code_r0x0015e5a8;
            case 0xf0:
              goto code_r0x0015e480;
            }
          case 0x60:
            goto code_r0x0015e578;
          case 0x78:
            goto code_r0x0015e62c;
          case 0x80:
            goto code_r0x0015e694;
          case 0x88:
            goto code_r0x0015e60c;
          case 0xa0:
            goto code_r0x0015e494;
          case 0xa8:
            goto code_r0x0015e748;
          case 0xb0:
            goto code_r0x0015e678;
          case 0xc0:
            goto code_r0x0015e58c;
          case 200:
            goto code_r0x0015e4dc;
          case 0xd0:
            goto code_r0x0015e5e8;
          case 0xd8:
            goto code_r0x0015e628;
          }
        case 0x40:
          goto code_r0x0015e664;
        case 0x48:
          goto code_r0x0015e608;
        case 0x50:
          goto code_r0x0015e6b0;
        case 0x58:
          goto code_r0x0015e5cc;
        case 0x60:
          goto code_r0x0015e578;
        case 0x78:
          goto code_r0x0015e62c;
        case 0x80:
          goto code_r0x0015e694;
        case 0x88:
          goto code_r0x0015e60c;
        case 0xa0:
          goto code_r0x0015e494;
        case 0xa8:
          goto code_r0x0015e748;
        case 0xb0:
          goto code_r0x0015e678;
        case 0xc0:
          goto code_r0x0015e58c;
        case 200:
          goto code_r0x0015e4dc;
        case 0xd0:
          goto code_r0x0015e5e8;
        case 0xd8:
          goto code_r0x0015e628;
        case 0xe0:
          goto code_r0x0015e5a8;
        case 0xe8:
          goto code_r0x0015e648;
        case 0xf0:
          goto code_r0x0015e480;
        case 0xf8:
          goto code_r0x0015e764;
        case 0x100:
          goto code_r0x0015e4a8;
        case 0x120:
          goto code_r0x0015e50c;
        case 0x128:
          goto code_r0x0015e5b8;
        }
      case 0x28:
code_r0x0015e6c0:
        uVar1 = 0x18;
        if (iVar3 != 0x3b21f150) {
          uVar1 = 8;
        }
        switch(uVar1) {
        case 0:
          goto code_r0x0015e77c;
        case 8:
          goto code_r0x0015e46c;
        case 0x10:
          goto code_r0x0015e4f0;
        }
      case 0x18:
code_r0x0015e6dc:
        iVar2 = func_0x001fdc04(param_1);
        iVar3 = 0x30fae711;
        if (iVar2 != 0) {
          iVar3 = 0x5ad22f2f;
        }
        break;
      case 0x38:
        goto code_r0x0015e5ec;
      case 0x40:
        goto code_r0x0015e664;
      case 0x48:
code_r0x0015e608:
      case 0x50:
        goto code_r0x0015e6b0;
      case 0x58:
        goto code_r0x0015e5cc;
      case 0x60:
        goto code_r0x0015e578;
      case 0x78:
        goto code_r0x0015e62c;
      case 0x80:
        goto code_r0x0015e694;
      case 0x88:
        goto code_r0x0015e60c;
      case 0xa0:
        goto code_r0x0015e494;
      case 0xa8:
        goto code_r0x0015e748;
      case 0xb0:
        goto code_r0x0015e678;
      case 0xc0:
        goto code_r0x0015e58c;
      case 200:
        goto code_r0x0015e4dc;
      case 0xd0:
        goto code_r0x0015e5e8;
      case 0xd8:
code_r0x0015e628:
        goto code_r0x0015e6b0;
      case 0xe0:
        goto code_r0x0015e5a8;
      case 0xe8:
        goto code_r0x0015e648;
      case 0xf0:
        goto code_r0x0015e480;
      case 0xf8:
code_r0x0015e764:
        lStack_68 = lStack_80;
        iVar3 = -0xf84ebb9;
        if (lStack_80 != 0) {
          iVar3 = 0x44b82855;
        }
        break;
      case 0x100:
        goto code_r0x0015e4a8;
      case 0x120:
code_r0x0015e50c:
        iVar2 = func_0x0015e7a4(lStack_68);
        iVar3 = 0x3b21f150;
        if (iVar2 != 0) {
          iVar3 = 0x5d7b4e5a;
        }
        break;
      case 0x128:
        goto code_r0x0015e5b8;
      }
    case 0x20:
      goto code_r0x0015e4c8;
    case 0x40:
code_r0x0015e664:
      unaff_w20 = 0x10004;
      iVar3 = -0x7c5650aa;
      break;
    case 0x60:
      goto code_r0x0015e578;
    case 0x80:
      goto code_r0x0015e694;
    case 0xa0:
      goto code_r0x0015e494;
    case 0xb0:
      goto code_r0x0015e678;
    case 0xc0:
      goto code_r0x0015e58c;
    case 0xd0:
code_r0x0015e5e8:
    case 0x50:
code_r0x0015e6b0:
      unaff_w20 = 0xffffffff;
      iVar3 = -0x7c5650aa;
      break;
    case 0xe0:
code_r0x0015e5a8:
      iVar3 = 0x6e221a17;
      if (iStack_6c != 0) {
        iVar3 = 0x6e142ec8;
      }
      break;
    case 0xf0:
      goto code_r0x0015e480;
    }
  } while( true );
code_r0x0015e4a8:
  uVar1 = 0;
  if (iVar3 != -0x7c5650aa) {
    uVar1 = 0x70;
  }
  switch(uVar1) {
  case 0:
    goto code_r0x0015e77c;
  case 0x10:
    goto code_r0x0015e4f0;
  case 0x20:
    goto code_r0x0015e4c8;
  default:
    goto code_r0x0015e46c;
  case 0x40:
    goto code_r0x0015e664;
  case 0x50:
    goto code_r0x0015e6b0;
  case 0x60:
    goto code_r0x0015e578;
  }
}


// ===== unwind_xx_info_query @ 001de1cc =====

long unwind_xx_info_query(char *param_1,long param_2,long param_3)

{
  undefined *puVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  long lStack_48;
  long lStack_40;
  undefined1 auStack_38 [8];
  
  uVar2 = func_0x001fee2c();
  if (param_1 == (char *)0x0) {
    lVar3 = 0;
  }
  else {
    lVar3 = 0;
    if (((param_3 != 0) && (param_2 != 0)) && (*param_1 != '\0')) {
      uVar4 = func_0x001f10f8(0);
      func_0x001f1054(auStack_38,uVar4);
      lStack_48 = 0;
      lStack_40 = 0;
      func_0x00162b6c(&lStack_48,param_1);
      lVar3 = func_0x001db2e8(uVar2,&lStack_48);
      if (lStack_48 != 0) {
        func_0x001e6248(lStack_48,lStack_40 + 1);
      }
      if (lVar3 == 0) {
        lVar3 = 0;
      }
      else {
        puVar1 = &UNK_0021ff95;
        if (*(undefined **)(lVar3 + 0x28) != (undefined *)0x0) {
          puVar1 = *(undefined **)(lVar3 + 0x28);
        }
        func_0x001f5d58(param_2,puVar1,param_3);
        lVar3 = param_2;
      }
      func_0x001f1060(auStack_38);
    }
  }
  return lVar3;
}


// ===== sleep @ 00261000 =====

/* WARNING: Control flow encountered bad instruction data */

void sleep(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== mprotect @ 00261008 =====

/* WARNING: Control flow encountered bad instruction data */

void mprotect(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== sem_wait @ 00261010 =====

/* WARNING: Control flow encountered bad instruction data */

void sem_wait(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __strrchr_chk @ 00261018 =====

/* WARNING: Control flow encountered bad instruction data */

void __strrchr_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pthread_mutex_destroy @ 00261020 =====

/* WARNING: Control flow encountered bad instruction data */

void pthread_mutex_destroy(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== atoi @ 00261028 =====

/* WARNING: Control flow encountered bad instruction data */

void atoi(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pthread_create @ 00261030 =====

/* WARNING: Control flow encountered bad instruction data */

void pthread_create(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== realloc @ 00261038 =====

/* WARNING: Control flow encountered bad instruction data */

void realloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __vsnprintf_chk @ 00261040 =====

/* WARNING: Control flow encountered bad instruction data */

void __vsnprintf_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== sem_post @ 00261048 =====

/* WARNING: Control flow encountered bad instruction data */

void sem_post(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pthread_attr_setdetachstate @ 00261050 =====

/* WARNING: Control flow encountered bad instruction data */

void pthread_attr_setdetachstate(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pthread_once @ 00261058 =====

/* WARNING: Control flow encountered bad instruction data */

void pthread_once(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __cxa_finalize @ 00261060 =====

/* WARNING: Control flow encountered bad instruction data */

void __cxa_finalize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== ftell @ 00261068 =====

/* WARNING: Control flow encountered bad instruction data */

void ftell(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pow @ 00261070 =====

/* WARNING: Control flow encountered bad instruction data */

void pow(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== isalpha @ 00261078 =====

/* WARNING: Control flow encountered bad instruction data */

void isalpha(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __FD_ISSET_chk @ 00261080 =====

/* WARNING: Control flow encountered bad instruction data */

void __FD_ISSET_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== mkdir @ 00261088 =====

/* WARNING: Control flow encountered bad instruction data */

void mkdir(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== calloc @ 00261090 =====

/* WARNING: Control flow encountered bad instruction data */

void calloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fread @ 00261098 =====

/* WARNING: Control flow encountered bad instruction data */

void fread(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== getcwd @ 002610a0 =====

/* WARNING: Control flow encountered bad instruction data */

void getcwd(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== settimeofday @ 002610a8 =====

/* WARNING: Control flow encountered bad instruction data */

void settimeofday(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== strncmp @ 002610b0 =====

/* WARNING: Control flow encountered bad instruction data */

void strncmp(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== read @ 002610b8 =====

/* WARNING: Control flow encountered bad instruction data */

void read(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __strlen_chk @ 002610c0 =====

/* WARNING: Control flow encountered bad instruction data */

void __strlen_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fstat @ 002610c8 =====

/* WARNING: Control flow encountered bad instruction data */

void fstat(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pthread_mutex_init @ 002610d0 =====

/* WARNING: Control flow encountered bad instruction data */

void pthread_mutex_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== atof @ 002610d8 =====

/* WARNING: Control flow encountered bad instruction data */

void atof(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== vsnprintf @ 002610e0 =====

/* WARNING: Control flow encountered bad instruction data */

void vsnprintf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== closedir @ 002610e8 =====

/* WARNING: Control flow encountered bad instruction data */

void closedir(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __errno @ 002610f0 =====

/* WARNING: Control flow encountered bad instruction data */

void __errno(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== sem_timedwait @ 002610f8 =====

/* WARNING: Control flow encountered bad instruction data */

void sem_timedwait(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== srand @ 00261100 =====

/* WARNING: Control flow encountered bad instruction data */

void srand(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== getpid @ 00261108 =====

/* WARNING: Control flow encountered bad instruction data */

void getpid(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __memcpy_chk @ 00261110 =====

/* WARNING: Control flow encountered bad instruction data */

void __memcpy_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== _ZdlPv @ 00261118 =====

/* WARNING: Control flow encountered bad instruction data */

void _ZdlPv(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== sscanf @ 00261120 =====

/* WARNING: Control flow encountered bad instruction data */

void sscanf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== write @ 00261128 =====

/* WARNING: Control flow encountered bad instruction data */

void write(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== getenv @ 00261130 =====

/* WARNING: Control flow encountered bad instruction data */

void getenv(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== random @ 00261138 =====

/* WARNING: Control flow encountered bad instruction data */

void random(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== strrchr @ 00261140 =====

/* WARNING: Control flow encountered bad instruction data */

void strrchr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== access @ 00261148 =====

/* WARNING: Control flow encountered bad instruction data */

void access(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== time @ 00261150 =====

/* WARNING: Control flow encountered bad instruction data */

void time(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== rand @ 00261158 =====

/* WARNING: Control flow encountered bad instruction data */

void rand(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __read_chk @ 00261160 =====

/* WARNING: Control flow encountered bad instruction data */

void __read_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fclose @ 00261168 =====

/* WARNING: Control flow encountered bad instruction data */

void fclose(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== lseek @ 00261170 =====

/* WARNING: Control flow encountered bad instruction data */

void lseek(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== madvise @ 00261178 =====

/* WARNING: Control flow encountered bad instruction data */

void madvise(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== freeaddrinfo @ 00261180 =====

/* WARNING: Control flow encountered bad instruction data */

void freeaddrinfo(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fputs @ 00261188 =====

/* WARNING: Control flow encountered bad instruction data */

void fputs(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fflush @ 00261190 =====

/* WARNING: Control flow encountered bad instruction data */

void fflush(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== recvfrom @ 00261198 =====

/* WARNING: Control flow encountered bad instruction data */

void recvfrom(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fputc @ 002611a0 =====

/* WARNING: Control flow encountered bad instruction data */

void fputc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __cxa_pure_virtual @ 002611a8 =====

/* WARNING: Control flow encountered bad instruction data */

void __cxa_pure_virtual(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fgets @ 002611b0 =====

/* WARNING: Control flow encountered bad instruction data */

void fgets(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== _Znwm @ 002611b8 =====

/* WARNING: Control flow encountered bad instruction data */

void _Znwm(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pthread_attr_init @ 002611c0 =====

/* WARNING: Control flow encountered bad instruction data */

void pthread_attr_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== select @ 002611c8 =====

/* WARNING: Control flow encountered bad instruction data */

void select(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __FD_SET_chk @ 002611d0 =====

/* WARNING: Control flow encountered bad instruction data */

void __FD_SET_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== gettimeofday @ 002611d8 =====

/* WARNING: Control flow encountered bad instruction data */

void gettimeofday(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== dlclose @ 002611e0 =====

/* WARNING: Control flow encountered bad instruction data */

void dlclose(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== feof @ 002611e8 =====

/* WARNING: Control flow encountered bad instruction data */

void feof(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fileno @ 002611f0 =====

/* WARNING: Control flow encountered bad instruction data */

void fileno(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== strtok_r @ 002611f8 =====

/* WARNING: Control flow encountered bad instruction data */

void strtok_r(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== nanosleep @ 00261200 =====

/* WARNING: Control flow encountered bad instruction data */

void nanosleep(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== strcasestr @ 00261208 =====

/* WARNING: Control flow encountered bad instruction data */

void strcasestr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== strncpy @ 00261210 =====

/* WARNING: Control flow encountered bad instruction data */

void strncpy(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== opendir @ 00261218 =====

/* WARNING: Control flow encountered bad instruction data */

void opendir(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== sendto @ 00261220 =====

/* WARNING: Control flow encountered bad instruction data */

void sendto(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== inet_ntop @ 00261228 =====

/* WARNING: Control flow encountered bad instruction data */

void inet_ntop(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== dlsym @ 00261230 =====

/* WARNING: Control flow encountered bad instruction data */

void dlsym(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== unlink @ 00261238 =====

/* WARNING: Control flow encountered bad instruction data */

void unlink(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pthread_attr_destroy @ 00261240 =====

/* WARNING: Control flow encountered bad instruction data */

void pthread_attr_destroy(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pread @ 00261248 =====

/* WARNING: Control flow encountered bad instruction data */

void pread(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== strchr @ 00261250 =====

/* WARNING: Control flow encountered bad instruction data */

void strchr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== tolower @ 00261258 =====

/* WARNING: Control flow encountered bad instruction data */

void tolower(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __strchr_chk @ 00261260 =====

/* WARNING: Control flow encountered bad instruction data */

void __strchr_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fseek @ 00261268 =====

/* WARNING: Control flow encountered bad instruction data */

void fseek(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== strcmp @ 00261270 =====

/* WARNING: Control flow encountered bad instruction data */

void strcmp(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __open_2 @ 00261278 =====

/* WARNING: Control flow encountered bad instruction data */

void __open_2(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pthread_attr_setstacksize @ 00261280 =====

/* WARNING: Control flow encountered bad instruction data */

void pthread_attr_setstacksize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== _Znam @ 00261288 =====

/* WARNING: Control flow encountered bad instruction data */

void _Znam(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pthread_mutex_lock @ 00261290 =====

/* WARNING: Control flow encountered bad instruction data */

void pthread_mutex_lock(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== mmap @ 00261298 =====

/* WARNING: Control flow encountered bad instruction data */

void mmap(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== inet_pton @ 002612a0 =====

/* WARNING: Control flow encountered bad instruction data */

void inet_pton(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== memmove @ 002612a8 =====

/* WARNING: Control flow encountered bad instruction data */

void memmove(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== ferror @ 002612b0 =====

/* WARNING: Control flow encountered bad instruction data */

void ferror(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== sem_init @ 002612b8 =====

/* WARNING: Control flow encountered bad instruction data */

void sem_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== getuid @ 002612c0 =====

/* WARNING: Control flow encountered bad instruction data */

void getuid(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __vsprintf_chk @ 002612c8 =====

/* WARNING: Control flow encountered bad instruction data */

void __vsprintf_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== readlink @ 002612d0 =====

/* WARNING: Control flow encountered bad instruction data */

void readlink(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== strstr @ 002612d8 =====

/* WARNING: Control flow encountered bad instruction data */

void strstr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __memset_chk @ 002612e0 =====

/* WARNING: Control flow encountered bad instruction data */

void __memset_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== usleep @ 002612e8 =====

/* WARNING: Control flow encountered bad instruction data */

void usleep(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== dladdr @ 002612f0 =====

/* WARNING: Control flow encountered bad instruction data */

void dladdr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== readdir @ 002612f8 =====

/* WARNING: Control flow encountered bad instruction data */

void readdir(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== strlen @ 00261300 =====

/* WARNING: Control flow encountered bad instruction data */

void strlen(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== close @ 00261308 =====

/* WARNING: Control flow encountered bad instruction data */

void close(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== remove @ 00261310 =====

/* WARNING: Control flow encountered bad instruction data */

void remove(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== dlopen @ 00261318 =====

/* WARNING: Control flow encountered bad instruction data */

void dlopen(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== stat @ 00261320 =====

/* WARNING: Control flow encountered bad instruction data */

void stat(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== localtime @ 00261328 =====

/* WARNING: Control flow encountered bad instruction data */

void localtime(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== rename @ 00261330 =====

/* WARNING: Control flow encountered bad instruction data */

void rename(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== munmap @ 00261338 =====

/* WARNING: Control flow encountered bad instruction data */

void munmap(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fprintf @ 00261340 =====

/* WARNING: Control flow encountered bad instruction data */

void fprintf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== malloc @ 00261348 =====

/* WARNING: Control flow encountered bad instruction data */

void malloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== memcpy @ 00261350 =====

/* WARNING: Control flow encountered bad instruction data */

void memcpy(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== isalnum @ 00261358 =====

/* WARNING: Control flow encountered bad instruction data */

void isalnum(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== connect @ 00261360 =====

/* WARNING: Control flow encountered bad instruction data */

void connect(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== memset @ 00261368 =====

/* WARNING: Control flow encountered bad instruction data */

void memset(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fopen @ 00261370 =====

/* WARNING: Control flow encountered bad instruction data */

void fopen(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== socket @ 00261378 =====

/* WARNING: Control flow encountered bad instruction data */

void socket(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fwrite @ 00261380 =====

/* WARNING: Control flow encountered bad instruction data */

void fwrite(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== fcntl @ 00261388 =====

/* WARNING: Control flow encountered bad instruction data */

void fcntl(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== free @ 00261390 =====

/* WARNING: Control flow encountered bad instruction data */

void free(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== pthread_mutex_unlock @ 00261398 =====

/* WARNING: Control flow encountered bad instruction data */

void pthread_mutex_unlock(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== clock_gettime @ 002613a0 =====

/* WARNING: Control flow encountered bad instruction data */

void clock_gettime(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== __cxa_atexit @ 002613a8 =====

/* WARNING: Control flow encountered bad instruction data */

void __cxa_atexit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== _ZdaPv @ 002613b0 =====

/* WARNING: Control flow encountered bad instruction data */

void _ZdaPv(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== getaddrinfo @ 002613b8 =====

/* WARNING: Control flow encountered bad instruction data */

void getaddrinfo(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ===== isspace @ 002613c0 =====

/* WARNING: Control flow encountered bad instruction data */

void isspace(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

