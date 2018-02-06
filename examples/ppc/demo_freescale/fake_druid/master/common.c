#include "ee.h"


/***************************************************************************
 *
 * Remote Notification
 *
 **************************************************************************/
    #pragma section EE_SHARED_CONST_BEGIN /* allocate into shared const data section */
    #pragma section EE_SHARED_SCONST_BEGIN /* allocate into shared sconst data section */
    const EE_UINT8 EE_rn_cpu[EE_MAX_RN] =
        { 0U, 0U, 0U, 0U, 1U, 1U};
    #pragma section EE_SHARED_CONST_END /* pragma tail */
    #pragma section EE_SHARED_SCONST_END /* pragma tail */

    #if defined( __RN_EVENT__ ) || defined( __RN_TASK__ )
        #pragma section EE_SHARED_CONST_BEGIN /* allocate into shared const data section */
        #pragma section EE_SHARED_SCONST_BEGIN /* allocate into shared sconst data section */
        const EE_TID EE_rn_task[EE_MAX_RN] = {
            0,		 /* cpu_0 - thread TaskZ6_1 */
            1,		 /* cpu_0 - thread TaskZ6_2 */
            2,		 /* cpu_0 - thread TaskZ6_3 */
            3,		 /* cpu_0 - thread TaskZ6_4 */
            0,		 /* cpu_1 - thread disturbing_task */
            1		 /* cpu_1 - thread CheckOK_task */
        };
        #pragma section EE_SHARED_CONST_END /* pragma tail */
        #pragma section EE_SHARED_SCONST_END /* pragma tail */
    #endif

    /* For each RN: The type of notification that must be used
     * EE_RN_COUNTER, EE_RN_EVENT, EE_RN_TASK,
     * EE_RN_FUNC, EE_RN_SEM
     */
    #pragma section EE_SHARED_BEGIN /* allocate into initialized shared data section */
    #pragma section EE_SHARED_FAST_BEGIN /* allocate into initialized shared fast data section */
    EE_TYPERN_NOTIFY EE_rn_type[EE_MAX_RN][2] = {
        {0U, 0U},		 /* cpu_0 - thread TaskZ6_1 */
        {0U, 0U},		 /* cpu_0 - thread TaskZ6_2 */
        {0U, 0U},		 /* cpu_0 - thread TaskZ6_3 */
        {0U, 0U},		 /* cpu_0 - thread TaskZ6_4 */
        {0U, 0U},		 /* cpu_1 - thread disturbing_task */
        {0U, 0U}		 /* cpu_1 - thread CheckOK_task */
    };
    #pragma section EE_SHARED_END /* pragma tail */
    #pragma section EE_SHARED_FAST_END /* pragma tail */

    /* For each RN: The counter number if EE_RN_COUNTER, or -1 */
    #ifdef __RN_COUNTER__
        #pragma section EE_SHARED_CONST_BEGIN /* allocate into shared const data section */
        #pragma section EE_SHARED_SCONST_BEGIN /* allocate into shared sconst data section */
        const EE_TYPECOUNTER EE_rn_counter[EE_MAX_RN] =
            {-1, -1, -1, -1, -1, -1};
        #pragma section EE_SHARED_CONST_END /* pragma tail */
        #pragma section EE_SHARED_SCONST_END /* pragma tail */
    #endif

    #ifdef __RN_EVENT__
        #pragma section EE_SHARED_BEGIN /* allocate into initialized shared data section */
        #pragma section EE_SHARED_FAST_BEGIN /* allocate into initialized shared fast data section */
        EE_TYPEEVENTMASK EE_rn_event[EE_MAX_RN][2] = {
            {0U, 0U},
            {0U, 0U},
            {0U, 0U},
            {0U, 0U},
            {0U, 0U},
            {0U, 0U}
        };
        #pragma section EE_SHARED_END /* pragma tail */
        #pragma section EE_SHARED_FAST_END /* pragma tail */
    #endif

    #pragma section EE_SHARED_BEGIN /* allocate into initialized shared data section */
    #pragma section EE_SHARED_FAST_BEGIN /* allocate into initialized shared fast data section */
    EE_TYPERN EE_rn_next[EE_MAX_RN][2] = {
            {-1, -1},
            {-1, -1},
            {-1, -1},
            {-1, -1},
            {-1, -1},
            {-1, -1}
    };
    #pragma section EE_SHARED_END /* pragma tail */
    #pragma section EE_SHARED_FAST_END /* pragma tail */

    #pragma section EE_SHARED_BEGIN /* allocate into initialized shared data section */
    #pragma section EE_SHARED_FAST_BEGIN /* allocate into initialized shared fast data section */
    EE_UREG EE_rn_pending[EE_MAX_RN][2] = {
        {0U, 0U},
        {0U, 0U},
        {0U, 0U},
        {0U, 0U},
        {0U, 0U},
        {0U, 0U}
    };
    #pragma section EE_SHARED_END /* pragma tail */
    #pragma section EE_SHARED_FAST_END /* pragma tail */

    #ifdef __RN_FUNC__
        /* const EE_ADDR EE_rn_func[EE_MAX_RN] = {(EE_ADDR)f,...};*/
    #endif

    #ifdef __RN_SEM__
        /*EE_SEM * const EE_rn_sem[EE_MAX_RN];*/
    #endif

    #pragma section EE_SHARED_BEGIN /* allocate into initialized shared data section */
    #pragma section EE_SHARED_FAST_BEGIN /* allocate into initialized shared fast data section */
    EE_TYPERN EE_rn_first[EE_MAX_CPU][2] = {
        { -1, -1}, { -1, -1}
    };
    #pragma section EE_SHARED_END /* pragma tail */
    #pragma section EE_SHARED_FAST_END /* pragma tail */

    #pragma section EE_SHARED_CONST_BEGIN /* allocate into shared const data section */
    #pragma section EE_SHARED_SCONST_BEGIN /* allocate into shared sconst data section */
    const EE_TYPESPIN EE_rn_spin[EE_MAX_CPU] = { 0U, 1U};
    #pragma section EE_SHARED_CONST_END /* pragma tail */
    #pragma section EE_SHARED_SCONST_END /* pragma tail */

    #pragma section EE_SHARED_BEGIN /* allocate into initialized shared data section */
    #pragma section EE_SHARED_FAST_BEGIN /* allocate into initialized shared fast data section */
    EE_TYPERN_SWITCH EE_rn_switch[EE_MAX_CPU] = { 0U, 0U};
    #pragma section EE_SHARED_END /* pragma tail */
    #pragma section EE_SHARED_FAST_END /* pragma tail */

