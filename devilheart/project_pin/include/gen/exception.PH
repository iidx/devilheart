//Groups: @ingroup\s+(API_REF|KNOBS|IMG_BASIC_API|INS_BASIC_API|INS_INST_API|INS_BASIC_API_GEN_IA32|INS_BASIC_API_IA32|INS_BASIC_API_IPF|INS_MOD_API_GEN_IA32|SEC_BASIC_API|RTN_BASIC_API|REG_BASIC_API|REG_CPU_GENERIC|REG_CPU_IPF|REG_CPU_IA32|TRACE_BASIC_API|BBL_BASIC_API|SYM_BASIC_API|MISC_PRINT|MISC_PARSE|KNOB_API|KNOB_BASIC|KNOB_PRINT|LOCK|PIN_CONTROL|BUFFER_API|PROTO_API|PIN_PROCESS_API|PIN_THREAD_API|DEBUG_API|ERROR_FILE_BASIC|TYPE_BASE|INSTLIB|ALARM|ROGUE_EDG_BASIC_API|ROGUE_BBL_BASIC_API|ROGUE_INS_BASIC_API|ROGUE_TRACE_BASIC_API|ROGUE_CONTROL_BASIC_API|CODECACHE_API|CHILD_PROCESS_API|SUPERPIN_API|UTILS|IPF_UTILS_API|MISC|CONTEXT_API|CHECKPOINTING|EXCEPTION_API|APPDEBUG_API|BUFFER_API|PROTO|INST_ARGS|PIN_THREAD_PRIVATE|CHILD_PROCESS_INTERNAL|EDG_BASIC|BBL_BASIC|ROGUE_BASIC_API|CODECACHE_NYI_API|INS_BASIC_API_GEN_IPF|MESSAGE_TYPE|MESSAGE_BASIC|ERRFILE|MISC_BASIC|ITC_INST_API|CHECKPOINTING_PRIVATE|CONTEXT_API_UNDOC|EXCEPTION_API_UNDOC|SHADOW_PROFILING_UNDOC|UNDOCUMENTED_PIN_API|DEPRECATED_PIN_API|OPIN|TRACE_VERSIONS
/* PIN API */

/* THIS FILE IS AUTOMAGICALLY GENERATED - DO NOT CHANGE DIRECTLY*/


enum EXCEPTION_CLASS
{
    EXCEPTCLASS_NONE,                   ///< Reserved. Neither exception belongs to this class
    EXCEPTCLASS_ACCESS_FAULT,           ///< Memory access fault
    EXCEPTCLASS_INVALID_INS,            ///< Invalid instruction
    EXCEPTCLASS_INT_ERROR,              ///< Erroneous integer operation 
    EXCEPTCLASS_FP_ERROR,               ///< Erroneous floating point operation 
    EXCEPTCLASS_DEBUG,                  ///< Debugging trap
    EXCEPTCLASS_OS_SPECIFIC             ///< OS-specific exception
};

                                                                  /* DO NOT EDIT */
enum EXCEPTION_CODE
{
    EXCEPTCODE_NONE,                    ///< Reserved. Neither exception has this code
    EXCEPTCODE_ACCESS_FAULT,            ///< General memory access fault. 
                                        ///< Belongs to EXCEPTCLASS_ACCESS_FAULT.
    EXCEPTCODE_ACCESS_INVALID_ADDRESS,  ///< Virtual address is not mapped.
                                        ///< Belongs to EXCEPTCLASS_ACCESS_FAULT.
    EXCEPTCODE_ACCESS_INVALID_PAGE,     ///< Unavailable physical address.
                                        ///< Belongs to EXCEPTCLASS_ACCESS_FAULT.
    EXCEPTCODE_ACCESS_DENIED,           ///< Access is not permitted (protection violation). 
                                        ///< Belongs to EXCEPTCLASS_ACCESS_FAULT.
    EXCEPTCODE_ACCESS_MISALIGNED,       ///< Misaligned access.
                                        ///< Belongs to EXCEPTCLASS_ACCESS_FAULT.
    EXCEPTCODE_ACCESS_GUARD_PAGE,       ///< Guard page access. This exception can be reported 
                                        ///< only on systems that support guard pages, e.g. Windows. 
                                        ///< Belongs to EXCEPTCLASS_ACCESS_FAULT.
    EXCEPTCODE_ACCESS_STACK_OVERFLOW,   ///< Thread stack overflowed. On some systems this 
                                        ///< exception is reported as a general memory access fault. 
                                        ///< Belongs to EXCEPTCLASS_ACCESS_FAULT.
    EXCEPTCODE_ILLEGAL_INS,             ///< Illegal instruction.
                                        ///< Belongs to EXCEPTCLASS_INVALID_INS.
    EXCEPTCODE_ILLEGAL_INS_OPCODE,      ///< Illegal opcode.
                                        ///< Belongs to EXCEPTCLASS_INVALID_INS.
    EXCEPTCODE_ILLEGAL_INS_OPERAND,     ///< Illegal operand.
                                        ///< Belongs to EXCEPTCLASS_INVALID_INS.
    EXCEPTCODE_ILLEGAL_INS_ADDRMODE,    ///< Illegal addressing mode.
                                        ///< Belongs to EXCEPTCLASS_INVALID_INS.
    EXCEPTCODE_ILLEGAL_INS_TRAP,        ///< Illegal trap.
                                        ///< Belongs to EXCEPTCLASS_INVALID_INS.
    EXCEPTCODE_ILLEGAL_INS_COPROCESSOR, ///< Coprocessor error.
                                        ///< Belongs to EXCEPTCLASS_INVALID_INS.
    EXCEPTCODE_PRIVILEGED_INS,          ///< Privileged instruction.
                                        ///< Belongs to EXCEPTCLASS_INVALID_INS.
    EXCEPTCODE_PRIVILEGED_INS_OPCODE,   ///< Privileged opcode.
                                        ///< Belongs to EXCEPTCLASS_INVALID_INS.
    EXCEPTCODE_PRIVILEGED_INS_REGISTER, ///< Privileged register.
                                        ///< Belongs to EXCEPTCLASS_INVALID_INS.
    EXCEPTCODE_INT_DIVIDE_BY_ZERO,      ///< Integer divide by zero.
                                        ///< Belongs to EXCEPTCLASS_INT_ERROR.
    EXCEPTCODE_INT_OVERFLOW_TRAP,       ///< Integer overflow trap.
                                        ///< Belongs to EXCEPTCLASS_INT_ERROR.
    EXCEPTCODE_INT_BOUNDS_EXCEEDED,     ///< Array index is out of bounds ("#BR" exception 
                                        ///< in IA-32 and Intel(R) 64 architectures).
                                        ///< Belongs to EXCEPTCLASS_INT_ERROR.
    EXCEPTCODE_FP_DIVIDE_BY_ZERO,       ///< Floating point divide by zero.
                                        ///< Belongs to EXCEPTCLASS_FP_ERROR.
    EXCEPTCODE_FP_OVERFLOW,             ///< Floating point overflow.
                                        ///< Belongs to EXCEPTCLASS_FP_ERROR.
    EXCEPTCODE_FP_UNDERFLOW,            ///< Floating point underflow.
                                        ///< Belongs to EXCEPTCLASS_FP_ERROR.
    EXCEPTCODE_FP_INEXACT_RESULT,       ///< Floating point inexact result.
                                        ///< Belongs to EXCEPTCLASS_FP_ERROR.
    EXCEPTCODE_FP_INVALID_OPERATION,    ///< Invalid floating point operation.
                                        ///< Belongs to EXCEPTCLASS_FP_ERROR.
    EXCEPTCODE_FP_DENORMAL_OPERAND,     ///< Denormal floating point operand.
                                        ///< Belongs to EXCEPTCLASS_FP_ERROR.
    EXCEPTCODE_FP_STACK_ERROR,          ///< Floating point stack overflowed or underflowed.
                                        ///< Belongs to EXCEPTCLASS_FP_ERROR.
    EXCEPTCODE_DBG_BREAKPOINT_TRAP,     ///< Breakpoint trap.
                                        ///< Belongs to EXCEPTCLASS_DEBUG.
    EXCEPTCODE_DBG_SINGLE_STEP_TRAP,    ///< Trace trap.
                                        ///< Belongs to EXCEPTCLASS_DEBUG.
    EXCEPTCODE_OS_SPECIFIC              ///< OS-specific exception. 
                                        ///< Belongs to EXCEPTCLASS_OS_SPECIFIC.
};

                                                                  /* DO NOT EDIT */
enum FAULTY_ACCESS_TYPE
{
    FAULTY_ACCESS_TYPE_UNKNOWN, ///< Unknown access violation
    FAULTY_ACCESS_READ,         ///< Read access
    FAULTY_ACCESS_WRITE,        ///< Write access
    FAULTY_ACCESS_EXECUTE       ///< Execute access
};

                                                                  /* DO NOT EDIT */
const UINT32 MAX_SYS_EXCEPTION_ARGS = 5;

                                                                  /* DO NOT EDIT */
struct EXCEPTION_INFO
{
    /* ================================================================================== */
    // Generic exception information
    /* ================================================================================== */

    /*!
     * Initialize this structure with the given generic exception's attributes. Set "unknown" 
     * state for all exception-specific attributes. 
     * This function is useful when the specified exception code does not require any 
     * additional exception information or such information is not available. The function 
     * can not be used to initialize EXCEPTCODE_OS_SPECIFIC exception information.
     * @param[in]   exceptCode      exception code
     * @param[in]   exceptAddress   address of the instruction that caused the exception
     * @return reference to this structure
     */
    EXCEPTION_INFO & Init(EXCEPTION_CODE exceptCode, ADDRINT exceptAddress);

    /*!
     * @return The code of the exception
     */
    EXCEPTION_CODE GetExceptCode() const {return m_exceptCode;}

    /*!
     * @return The class of the exception
     */
    static EXCEPTION_CLASS GetExceptClass(EXCEPTION_CODE exceptCode);
    EXCEPTION_CLASS GetExceptClass() const {return GetExceptClass(m_exceptCode);}

    /*!
     * @return The address of the instruction that caused the exception
     */
    ADDRINT GetExceptAddress() const {return m_exceptAddress;}

    /*!
     * Set the address of the instruction that caused the exception
     */
    VOID SetExceptAddress(ADDRINT exceptAddress) {m_exceptAddress = exceptAddress;}

    /*!
     * @return TRUE if the specified exception is a trap. Traps are reported in the 
     *         context that represents state of registers after executing the 
     *         instruction that caused the trap. The exception address and the value
     *         of the PC register in the trap context are different.
     */
    static BOOL IsTrap(EXCEPTION_CODE exceptCode);
    BOOL IsTrap() const {return IsTrap(m_exceptCode);}

    /*!
     * Remove the exception information and initialize this structure as empty.
     */
    VOID Reset() {m_exceptCode = EXCEPTCODE_NONE;}

    /*!
     * @return TRUE, if this structure has been reset and does not contain a valid
     *         exception information.
     */
    BOOL IsEmpty() const {return (m_exceptCode == EXCEPTCODE_NONE);}

    /*!
     * @return The string representation of this structure.
     */
    string ToString() const;

  public:

    /* ================================================================================== */
    // EXCEPTCLASS_ACCESS_FAULT information
    /* ================================================================================== */

    /*!
     * Initialize this structure with the given attributes of an EXCEPTCLASS_ACCESS_FAULT 
     * exception.
     * @param[in]   exceptCode      exception code that specifies an EXCEPTCLASS_ACCESS_FAULT 
     *                              exception
     * @param[in]   exceptAddress   address of the instruction that caused the exception
     * @param[in]   accessAddress   address of the faulty memory access
     * @param[in]   accessType      type of the faulty memory access
     * @return reference to this structure
     */
    EXCEPTION_INFO & InitAccessFault(EXCEPTION_CODE exceptCode,
                                     ADDRINT exceptAddress,
                                     ADDRINT accessAddress,
                                     FAULTY_ACCESS_TYPE accessType = FAULTY_ACCESS_TYPE_UNKNOWN);

    /*!
     * @return TRUE if this structure describes an EXCEPTCLASS_ACCESS_FAULT exception
     */
    BOOL IsAccessFault() const {return GetExceptClass() == EXCEPTCLASS_ACCESS_FAULT;}

    /*!
     * @return The type of the faulty memory access.
     * @pre    This structure should describe an EXCEPTCLASS_ACCESS_FAULT exception. 
     */
    FAULTY_ACCESS_TYPE GetFaultyAccessType() const 
    {
        ASSERTX(IsAccessFault()); 
        return m_specific.m_access.m_type;
    }

    /*!
     * Get the address of the faulty memory access, if known.
     * @param[out] pAccessAddress   optional pointer to variable that receives the address
     *                              of the faulty memory access, if known.
     * @return TRUE, if the address of the faulty memory access is known
     * @pre    This structure should describe an EXCEPTCLASS_ACCESS_FAULT exception. 
     */
    BOOL GetFaultyAccessAddress(ADDRINT * pAccessAddress) const 
    {
        ASSERTX(IsAccessFault());
        return m_specific.m_access.m_address.Get(pAccessAddress);
    }

  public:

    /* ================================================================================== */
    // EXCEPTCODE_OS_SPECIFIC information
    /* ================================================================================== */

    /*!
     * Initialize this structure with the given attributes of an EXCEPTCODE_OS_SPECIFIC 
     * exception.
     * @param[in]   sysExceptCode   the system exception code
     * @param[in]   exceptAddress   address of the instruction that caused the exception
     * @param[in]   numArgs         number of arguments in the [pArgs] array. The number 
     *                              should not exceed the MAX_SYS_EXCEPTION_ARGS value.
     * @param[in]   pArgs           pointer to an array of arguments associated with the exception 
     *                              or NULL if the number of arguments is zero
     * @return reference to this structure
     */
    EXCEPTION_INFO & InitSysException(UINT32 sysExceptCode,
                                      ADDRINT exceptAddress,
                                      UINT32 numArgs = 0,
                                      const ADDRINT * pArgs = 0);

    /*!
     * @return TRUE if this structure describes an EXCEPTCODE_OS_SPECIFIC exception
     */
    BOOL IsSysException() const {return m_exceptCode == EXCEPTCODE_OS_SPECIFIC;}

    /*!
     * @return The system exception code
     * @pre    This structure should describe an EXCEPTCODE_OS_SPECIFIC exception. 
     */
    UINT32 GetSysExceptionCode() const 
    {
        ASSERTX(IsSysException());
        return m_specific.m_sys.m_exceptCode;
    }

    /*!
     * @return The number of arguments associated with the system exception
     * @pre    This structure should describe an EXCEPTCODE_OS_SPECIFIC exception. 
     */
    UINT32 CountSysArguments() const 
    {
        ASSERTX(IsSysException());
        return m_specific.m_sys.m_numArgs;
    }

    /*!
     * Get the specified system exception's argument.
     * @param[in]   argNum          ordinal number of the argument to be retrieved, starting 
     *                              from zero. The value of this parameter should not exceed
     *                              the value returned by the CountSysArguments() function.
     * @return The value of the specified system exception's argument
     * @pre    This structure should describe an EXCEPTCODE_OS_SPECIFIC exception. 
     */
    ADDRINT GetSysArgument(UINT32 argNum) const 
    {
        ASSERTX(IsSysException());
        ASSERTX(argNum < m_specific.m_sys.m_numArgs);
        return m_specific.m_sys.m_args[argNum];
    }

  public:

    /* ================================================================================== */
    // Data
    /* ================================================================================== */
    EXCEPTION_CODE m_exceptCode;                    ///< Exception code
    ADDRINT m_exceptAddress;                        ///< Address of the faulty instruction

    /*!
     * Exception-specific data
     */
    union EXCEPTION_SPECIFIC
    {
        struct ACCESS_FAULT                         ///< EXCEPTCLASS_ACCESS_FAULT additional information
        {
            FAULTY_ACCESS_TYPE m_type;              ///< The type of the faulty memory access
            OPTIONAL_VALUE<ADDRINT> m_address;      ///< Address of the faulty memory access (optional)
        }m_access;

        struct OS_SPECIFIC                          ///< EXCEPTCODE_OS_SPECIFIC additional information
        {
            UINT32 m_exceptCode;                    ///< The system exception code or signal number
            UINT32 m_numArgs;                       ///< Number of arguments in the [m_args] array
            ADDRINT m_args[MAX_SYS_EXCEPTION_ARGS]; ///< Array of arguments associated with the exception
        }m_sys;
    }m_specific;
};

                                                                  /* DO NOT EDIT */
typedef struct EXCEPTION_INFO EXCEPTION_INFO;

                                                                  /* DO NOT EDIT */
inline VOID PIN_InitExceptionInfo(EXCEPTION_INFO * pExceptInfo,
                                        EXCEPTION_CODE exceptCode, 
                                        ADDRINT exceptAddress)
{
    pExceptInfo->Init(exceptCode, exceptAddress);
}

                                                                  /* DO NOT EDIT */
inline VOID PIN_InitAccessFaultInfo(EXCEPTION_INFO * pExceptInfo,
                                          EXCEPTION_CODE exceptCode,
                                          ADDRINT exceptAddress,
                                          ADDRINT accessAddress,
                                          FAULTY_ACCESS_TYPE accessType = FAULTY_ACCESS_TYPE_UNKNOWN)
{
    pExceptInfo->InitAccessFault(exceptCode, exceptAddress, accessAddress, accessType);
}

                                                                  /* DO NOT EDIT */
inline VOID PIN_InitSysExceptionInfo(EXCEPTION_INFO * pExceptInfo,
                                           UINT32 sysExceptCode,
                                           ADDRINT exceptAddress,
                                           UINT32 numArgs = 0,
                                           const ADDRINT * pArgs = 0)
{
    pExceptInfo->InitSysException(sysExceptCode, exceptAddress, numArgs, pArgs);
}

                                                                  /* DO NOT EDIT */
inline EXCEPTION_CODE PIN_GetExceptionCode(const EXCEPTION_INFO * pExceptInfo)
{
    return pExceptInfo->GetExceptCode();
}

                                                                  /* DO NOT EDIT */
inline EXCEPTION_CLASS PIN_GetExceptionClass(EXCEPTION_CODE exceptCode)
{
    return EXCEPTION_INFO::GetExceptClass(exceptCode);
}

                                                                  /* DO NOT EDIT */
inline ADDRINT PIN_GetExceptionAddress(const EXCEPTION_INFO * pExceptInfo)
{
    return pExceptInfo->GetExceptAddress();
}

                                                                  /* DO NOT EDIT */
inline VOID PIN_SetExceptionAddress(EXCEPTION_INFO * pExceptInfo, 
                                          ADDRINT exceptAddress)
{
    pExceptInfo->SetExceptAddress(exceptAddress);
}

                                                                  /* DO NOT EDIT */
inline FAULTY_ACCESS_TYPE PIN_GetFaultyAccessType(const EXCEPTION_INFO * pExceptInfo) 
{
    return pExceptInfo->GetFaultyAccessType();
}

                                                                  /* DO NOT EDIT */
inline BOOL PIN_GetFaultyAccessAddress(const EXCEPTION_INFO * pExceptInfo,
                                             ADDRINT * pAccessAddress) 
{
    return pExceptInfo->GetFaultyAccessAddress(pAccessAddress);
}

                                                                  /* DO NOT EDIT */
inline UINT32 PIN_GetSysExceptionCode(const EXCEPTION_INFO * pExceptInfo) 
{
    return pExceptInfo->GetSysExceptionCode();
}

                                                                  /* DO NOT EDIT */
inline UINT32 PIN_CountSysExceptionArguments(const EXCEPTION_INFO * pExceptInfo) 
{
    return pExceptInfo->CountSysArguments();
}

                                                                  /* DO NOT EDIT */
inline ADDRINT PIN_GetSysExceptionArgument(const EXCEPTION_INFO * pExceptInfo,
                                                UINT32 argNum) 
{
    return pExceptInfo->GetSysArgument(argNum);
}

                                                                  /* DO NOT EDIT */
inline string PIN_ExceptionToString(const EXCEPTION_INFO * pExceptInfo) 
{
    return pExceptInfo->ToString();
}

                                                                  /* DO NOT EDIT */

