#pragma once
#include <stdint.h>

void svc_beep_timed(uint16_t freq, uint16_t duration);
void svc_aux_timer_beep_handler(void);
void svc_beep_key_one_time_other_freq(void);

void svc_beep_key(void);
void svc_beep_hour(void);

void svc_beep_key_set_freq(uint16_t f);
uint16_t svc_beep_hour_get_freq(void);
void svc_beep_key_set_other_freq(uint16_t f);
uint16_t svc_beep_key_get_other_freq(void);
void svc_beep_key_set_duration(uint16_t d);
uint16_t svc_beep_key_get_duration(void);
void svc_beep_key_set_enable(uint8_t e);
uint8_t svc_beep_key_get_enable(void);

void svc_beep_hour_set_freq(uint16_t f);
uint16_t svc_beep_key_get_freq(void);
void svc_beep_hour_set_duration(uint16_t d);
uint16_t svc_beep_hour_get_duration(void);
void svc_beep_hour_set_enable(uint8_t e);
uint8_t svc_beep_hour_get_enable(void);
void svc_beep_hour_quiet_set_enable(uint8_t e);
uint8_t svc_beep_hour_quiet_get_enable(void);
void svc_beep_hour_quiet_set_interval(uint8_t s, uint8_t e);
void svc_beep_hour_quiet_get_interval(uint8_t *s, uint8_t *e);
