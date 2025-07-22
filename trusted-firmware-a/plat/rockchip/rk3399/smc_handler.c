#include <common/runtime_svc.h>
#include <lib/smccc.h>

/* SMC 函數 ID */
#define SMC_CUSTOM_ADD_ONE 0x82000001

/* SMC Handler 函數 */
static uintptr_t smc_add_one_handler(uint32_t smc_fid,
                                    u_register_t x1,
                                    u_register_t x2,
                                    u_register_t x3,
                                    u_register_t x4,
                                    void *cookie,
                                    void *handle,
                                    u_register_t flags)
{
    if (smc_fid == SMC_CUSTOM_ADD_ONE) {
        /* 將輸入 x (假設傳遞在 x1) 加 1 */
        u_register_t result = x1 + 1;

        /* 使用 SMC_CALL_RETURN 設置返回值 */
        SMC_RET1(handle, result);
    }

    /* 如果 SMC ID 不匹配，返回錯誤 */
    SMC_RET1(handle, SMC_UNK);
}

/* 註冊 SMC Handler */
DECLARE_RT_SVC(
    smc_add_one_svc,
    OEN_SIP_START,     
    OEN_SIP_END,
    SMC_TYPE_FAST,
    NULL,
    smc_add_one_handler
);

