#ifndef	__C_COMPILE_H__
#define __C_COMPILE_H__
//--------------------------------------------------------------------------------------------------
#define c_unused(x)       ( (void)(x) )
#define c_empty_statement ( (void)(0) )
#define cpp_inline        __inline
#define C_CHOICE(cond, if_exe, else_exe)	((cond) ? (if_exe) : (else_exe))
#define C_IF_ELSE(cond, if_exe, else_exe)  if ((cond)) (if_exe); else (else_exe)
//--------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------