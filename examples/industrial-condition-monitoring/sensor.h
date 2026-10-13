#ifndef SENSOR_H_
#define SENSOR_H_

#include <stdint.h>

/* =========================================================
 * Configuration (override in project-conf.h)
 * ========================================================= */

/* Length of the sampling window the RMS is computed over */
#ifdef APP_CONF_RMS_WINDOW_MS
#define RMS_WINDOW_MS APP_CONF_RMS_WINDOW_MS
#else
#define RMS_WINDOW_MS 80
#endif

/* Accelerometer sampling rate inside the window */
#ifdef APP_CONF_SAMPLE_RATE_HZ
#define SAMPLE_RATE_HZ APP_CONF_SAMPLE_RATE_HZ
#else
#define SAMPLE_RATE_HZ 1000
#endif

#define WINDOW_SAMPLES ((RMS_WINDOW_MS * SAMPLE_RATE_HZ) / 1000)

#if WINDOW_SAMPLES < 1 || WINDOW_SAMPLES > 1000
#error "RMS_WINDOW_MS * SAMPLE_RATE_HZ / 1000 must be in 1..1000"
#endif


/* =========================================================
 * API (all values in milli-g)
 * ========================================================= */

/* Fill one window of WINDOW_SAMPLES at SAMPLE_RATE_HZ (blocks RMS_WINDOW_MS) */
void sensor_sample_window(void);

/* Per-axis RMS of the last window, mean removed: rms[0..2] = x, y, z */
void sensor_window_rms(uint16_t rms[3]);

/* Sample i (0..WINDOW_SAMPLES-1) of the last window: xyz[0..2] = x, y, z */
void sensor_get_sample(uint16_t i, int16_t xyz[3]);

#endif /* SENSOR_H_ */
