#ifndef PACKET_FORMAT_H_
#define PACKET_FORMAT_H_

#include <stdint.h>

/*
 * Application packets, node -> coordinator (UDP 8185).
 *
 * Every packet starts with struct pkt_hdr; hdr.type says which struct
 * it is. All packets of one sampling window share the same seq.
 * Values are milli-g, sent in the JN516x's native (big-endian) order.
 */

#define PKT_RAW    1
#define PKT_ALERT  2
#define PKT_RMS    3

/* Samples per RAW packet */
#ifdef APP_CONF_RAW_SAMPLES_PER_PACKET
#define RAW_SAMPLES_PER_PACKET APP_CONF_RAW_SAMPLES_PER_PACKET
#else
#define RAW_SAMPLES_PER_PACKET 8
#endif

struct pkt_hdr {
  uint8_t type;      /* PKT_RAW / PKT_ALERT / PKT_RMS */
  uint8_t seq;       /* window counter, wraps at 256 */
  uint16_t node_id;
};

/* Periodic RMS of one window */
struct pkt_rms {
  struct pkt_hdr hdr;
  uint16_t x, y, z;
};

/* RMS over threshold; axes: bit0 = x, bit1 = y, bit2 = z */
struct pkt_alert {
  struct pkt_hdr hdr;
  uint16_t x, y, z;
  uint8_t axes;
};

/* One chunk of the raw window that caused an alert */
struct pkt_raw {
  struct pkt_hdr hdr;
  uint8_t index;     /* chunk number, first sample = index * RAW_SAMPLES_PER_PACKET */
  uint8_t count;     /* valid samples in xyz[] */
  int16_t xyz[RAW_SAMPLES_PER_PACKET][3];
};

#endif /* PACKET_FORMAT_H_ */
