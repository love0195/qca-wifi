/*
 * Copyright (c) 2011, Atheros Communications Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * LMAC WOW specific offload interface functions for UMAC
 */
#include "ol_if_athvar.h"
#include "wmi_unified_api.h"
#include "_ieee80211.h"
#include "ol_if_wow.h"

#if ATH_PERF_PWR_OFFLOAD && ATH_WOW

int
ol_wow_get_support(struct ieee80211com *ic)
{
    return 1;
}

int
ol_wow_enable(struct ieee80211com *ic, int clearbssid)
{
    struct ol_ath_softc_net80211 *scn = OL_ATH_SOFTC_NET80211(ic);
    A_STATUS res;
    wmi_buf_t buf = NULL;
    buf = wmi_buf_alloc(scn->wmi_handle, 4);
    if(!buf)
    {
        printk("buf alloc failed\n");
        return -ENOMEM;
    }
    res = wmi_unified_cmd_send(scn->wmi_handle, buf, 4, WMI_WOW_ENABLE_CMDID);
    printk("ol_wow_enable result: %d\n", res);
    return ((res == A_OK) ? EOK : -1);
}

int
ol_wow_wakeup(struct ieee80211com *ic)
{
    struct ol_ath_softc_net80211 *scn = OL_ATH_SOFTC_NET80211(ic);
    A_STATUS res;
    wmi_buf_t buf = NULL;
    buf = wmi_buf_alloc(scn->wmi_handle, 4);
    if(!buf)
    {
        printk("buf alloc failed\n");
        return -ENOMEM;
    }
    res = wmi_unified_cmd_send(scn->wmi_handle, buf, 4, WMI_WOW_HOSTWAKEUP_FROM_SLEEP_CMDID);
    printk("ol_wow_wakeup result: %d\n", res);
    return ((res == A_OK) ? EOK : -1);
}

int
ol_wow_add_wakeup_event(struct ieee80211com *ic, u_int32_t type)
{
    struct ol_ath_softc_net80211 *scn = OL_ATH_SOFTC_NET80211(ic);
    A_STATUS res;
    WMI_WOW_ADD_DEL_EVT_CMD *cmd;
    wmi_buf_t buf = NULL;
    int len = sizeof(WMI_WOW_ADD_DEL_EVT_CMD);
    buf = wmi_buf_alloc(scn->wmi_handle, len);
    if(!buf)
    {
        printk("buf alloc failed\n");
        return -ENOMEM;
    }
    cmd = (WMI_WOW_ADD_DEL_EVT_CMD *)wmi_buf_data(buf);
    cmd->is_add = 1;
    cmd->event_bitmap = type;
    res = wmi_unified_cmd_send(scn->wmi_handle, buf, len, WMI_WOW_ENABLE_DISABLE_WAKE_EVENT_CMDID);
    return ((res == A_OK) ? EOK : -1);
}

void
ol_wow_set_events(struct ieee80211com *ic, u_int32_t events)
{
    struct ol_ath_softc_net80211 *scn = OL_ATH_SOFTC_NET80211(ic);
    scn->scn_wowInfo->wakeUpEvents = events;
}

int
ol_wow_get_events(struct ieee80211com *ic)
{
    struct ol_ath_softc_net80211 *scn = OL_ATH_SOFTC_NET80211(ic);
    return (scn->scn_wowInfo->wakeUpEvents);
}

int
ol_wow_add_wakeup_pattern(struct ieee80211com *ic,
    u_int8_t *pattern_bytes, u_int8_t *mask_bytes, u_int32_t pattern_len)
{
    WOW_BITMAP_PATTERN_T bitmap_pattern;
    u_int32_t i, j;
    struct ol_wow_info  *wowInfo;
    OL_WOW_PATTERN *pattern;
    struct ol_ath_softc_net80211 *scn = OL_ATH_SOFTC_NET80211(ic);
    A_STATUS res;
    WMI_WOW_ADD_PATTERN_CMD *cmd;
    wmi_buf_t buf = NULL;
    int len = sizeof(WMI_WOW_ADD_PATTERN_CMD);
    
    ASSERT(scn->scn_wowInfo);
    wowInfo = scn->scn_wowInfo;
    
    // check for duplicate patterns 
    for (i = 0; i < MAX_NUM_USER_PATTERN; i++) {
        pattern = &wowInfo->patterns[i];
        if (pattern->valid) {
            if (!adf_os_mem_cmp(pattern_bytes, pattern->patternBytes, MAX_PATTERN_SIZE) &&
                (!adf_os_mem_cmp(mask_bytes, pattern->maskBytes, MAX_PATTERN_SIZE)))
            {
                printk("Pattern added already \n");
                return 0;
            }
        }
    }
    
    // find a empty pattern entry
    for (i = 0; i < MAX_NUM_USER_PATTERN; i++) {
        pattern = &wowInfo->patterns[i];
        if (!pattern->valid) {
            break;
        }
    }
    
    if (i == MAX_NUM_USER_PATTERN) {
        printk("Error : All the %d pattern are in use. Cannot add a new pattern \n", MAX_NUM_PATTERN);
        return (-1);
    }
    
    printk("Pattern added to entry %d \n",i);
    
    // add the pattern
    pattern = &wowInfo->patterns[i];
    adf_os_mem_copy(pattern->maskBytes, mask_bytes, MAX_PATTERN_SIZE);
    adf_os_mem_copy(pattern->patternBytes, pattern_bytes, MAX_PATTERN_SIZE);
    pattern->patternId  = i;
    pattern->patternLen = pattern_len;
    pattern->valid = 1;
    
    buf = wmi_buf_alloc(scn->wmi_handle, len);
    if(!buf)
    {
        printk("buf alloc failed\n");
        return -ENOMEM;
    }
    cmd = (WMI_WOW_ADD_PATTERN_CMD *)wmi_buf_data(buf);
    cmd->pattern_id = i;
    cmd->pattern_type = WOW_BITMAP_PATTERN;
    
    for(j=0 ; j<WOW_DEFAULT_BITMAP_PATTERN_SIZE; j++)
    {
        bitmap_pattern.patternbuf[j] = pattern_bytes[j];
        
    }
    for(j=0 ; j<WOW_DEFAULT_BITMASK_SIZE; j++)
    {
        bitmap_pattern.bitmaskbuf[j] = mask_bytes[j];
        
    }
    bitmap_pattern.pattern_offset = 0;
    
    cmd->pattern_info.bitmap = bitmap_pattern;
    res = wmi_unified_cmd_send(scn->wmi_handle, buf, len, WMI_WOW_ADD_WAKE_PATTERN_CMDID);
    
    return ((res == A_OK) ? EOK : -1);
}

int
ol_wow_remove_wakeup_pattern(struct ieee80211com *ic, u_int8_t *pattern_bytes,
    u_int8_t *mask_bytes)
{
    struct ol_ath_softc_net80211 *scn = OL_ATH_SOFTC_NET80211(ic);
    u_int32_t i;
    struct ol_wow_info  *wowInfo;
    OL_WOW_PATTERN *pattern;
    A_STATUS res;
    WMI_WOW_DEL_PATTERN_CMD *cmd;
    wmi_buf_t buf = NULL;
    int len = sizeof(WMI_WOW_DEL_PATTERN_CMD);
    
    ASSERT(scn->scn_wowInfo);
    wowInfo = scn->scn_wowInfo;
    
    printk("%s: Remove wake up pattern \n", __func__);
    
    // remove the pattern and return if present
    for (i = 0; i < MAX_NUM_USER_PATTERN; i++) {
        pattern = &wowInfo->patterns[i];
        if (pattern->valid) {
            if (!adf_os_mem_cmp(pattern_bytes, pattern->patternBytes, MAX_PATTERN_SIZE) &&
                !adf_os_mem_cmp(mask_bytes, pattern->maskBytes, MAX_PATTERN_SIZE))
            {
                pattern->valid = 0;
                adf_os_mem_zero(pattern->patternBytes, MAX_PATTERN_SIZE);
                adf_os_mem_zero(pattern->maskBytes, MAX_PATTERN_SIZE);
                printk("Pattern Removed from entry %d \n",i); 
                
                buf = wmi_buf_alloc(scn->wmi_handle, len);
                if(!buf)
                {
                    printk("buf alloc failed\n");
                    return -ENOMEM;
                }
                cmd = (WMI_WOW_DEL_PATTERN_CMD *)wmi_buf_data(buf);
                cmd->pattern_id = i;
                cmd->pattern_type = WOW_BITMAP_PATTERN;
                res = wmi_unified_cmd_send(scn->wmi_handle, buf, len, WMI_WOW_DEL_WAKE_PATTERN_CMDID);
                return ((res == A_OK) ? EOK : -1);
            }
        }
    }
    
    // pattern not found
    printk("%s : Error : Pattern not found \n", __func__);
    return (-1);
}

int
ol_wow_get_wakeup_pattern(struct ieee80211com *ic, u_int8_t *wake_pattern_bytes,
    u_int32_t *wake_pattern_size, u_int32_t *pattern_id)
{
    return 0;
}

int
ol_wow_get_wakeup_reason(struct ieee80211com *ic)
{
    struct ol_wow_info *wowInfo;
    struct ol_ath_softc_net80211 *scn = OL_ATH_SOFTC_NET80211(ic);
    ASSERT(scn->scn_wowInfo);
    wowInfo = scn->scn_wowInfo;
    return wowInfo->wowWakeupReason;
}

int
ol_wow_matchpattern_exact(struct ieee80211com *ic)
{
    return 0;
}

void
ol_wow_set_duration(struct ieee80211com *ic, u_int16_t duration)
{
}

void
ol_wow_set_timeout(struct ieee80211com *ic, u_int32_t timeoutinsecs)
{
}

u_int32_t
ol_wow_get_timeout(struct ieee80211com *ic) 
{
    return 0;
}

static int
wow_wakeup_host_event(ol_scn_t scn, u_int8_t *datap, u_int16_t len, void *context)
{
    struct ol_wow_info *wowInfo;
    wowInfo = scn->scn_wowInfo;
    wowInfo->wowWakeupReason = ((EVENT_INFO *)datap)->wake_reason;
    return 0;
}


/* Intialization functions */
int
ol_ath_wow_attach(struct ieee80211com *ic)
{
    struct ol_ath_softc_net80211 *scn = OL_ATH_SOFTC_NET80211(ic);

    scn->scn_wowInfo = (struct ol_wow_info *)adf_os_mem_alloc(scn->adf_dev, sizeof(struct ol_wow_info));
    if (scn->scn_wowInfo == NULL) {
        printk("%s: wowInfo allocation failed\n", __func__);
        return -1;
    }

    adf_os_mem_zero(scn->scn_wowInfo, sizeof(struct ol_wow_info));
    
    wmi_unified_register_event_handler(scn->wmi_handle, WMI_WOW_WAKEUP_HOST_EVENTID,
                                       wow_wakeup_host_event, NULL);

    /* Install WOW APIs */
    ic->ic_wow_get_support = ol_wow_get_support;
    ic->ic_wow_enable = ol_wow_enable;
    ic->ic_wow_wakeup = ol_wow_wakeup;
    ic->ic_wow_set_events = ol_wow_set_events;
    ic->ic_wow_get_events = ol_wow_get_events;
    ic->ic_wow_add_wakeup_event = ol_wow_add_wakeup_event;
    ic->ic_wow_add_wakeup_pattern = ol_wow_add_wakeup_pattern;
    ic->ic_wow_remove_wakeup_pattern = ol_wow_remove_wakeup_pattern;
    ic->ic_wow_get_wakeup_pattern = ol_wow_get_wakeup_pattern;
    ic->ic_wow_get_wakeup_reason = ol_wow_get_wakeup_reason;
    ic->ic_wow_matchpattern_exact = ol_wow_matchpattern_exact;
    ic->ic_wow_set_duration = ol_wow_set_duration;
    ic->ic_wow_set_timeout = ol_wow_set_timeout;
    ic->ic_wow_get_timeout = ol_wow_get_timeout;

    return 0;
}

int
ol_ath_wow_detach(struct ieee80211com *ic)
{
    struct ol_ath_softc_net80211 *scn = OL_ATH_SOFTC_NET80211(ic);

    if (!scn->scn_wowInfo) {
        return 0;
    }

    adf_os_mem_free(scn->scn_wowInfo);
    wmi_unified_unregister_event_handler(scn->wmi_handle, WMI_WOW_WAKEUP_HOST_EVENTID);


    /* Uninstall WOW APIs */
    ic->ic_wow_get_support = NULL;
    ic->ic_wow_enable = NULL;
    ic->ic_wow_wakeup = NULL;
    ic->ic_wow_set_events = NULL;
    ic->ic_wow_get_events = NULL;
    ic->ic_wow_add_wakeup_event = NULL;
    ic->ic_wow_add_wakeup_pattern = NULL;
    ic->ic_wow_remove_wakeup_pattern = NULL;
    ic->ic_wow_get_wakeup_pattern = NULL;
    ic->ic_wow_get_wakeup_reason = NULL;
    ic->ic_wow_matchpattern_exact = NULL;
    ic->ic_wow_set_duration = NULL;
    ic->ic_wow_set_timeout = NULL;
    ic->ic_wow_get_timeout = NULL;

    return 0;
}

#endif
