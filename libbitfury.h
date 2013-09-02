#ifndef __LIBBITFURY_H__
#define __LIBBITFURY_H__

#include "miner.h"
#include "spidevc.h"

#define BITFURY_STAT_N 1024

struct bitfury_payload {
	unsigned char midstate[32];
	unsigned int junk[8];
	unsigned m7;
	unsigned ntime;
	unsigned nbits;
	unsigned nnonce;
};

struct bitfury_device {
	struct spi_port *spi;
	unsigned char osc6_bits;
	unsigned newbuf[17];
	unsigned oldbuf[17];
	struct work * work;
	struct work * owork;
	struct work * o2work;
	int job_switched;
	struct bitfury_payload payload;
	struct bitfury_payload opayload;
	struct bitfury_payload o2payload;
	unsigned int results[16];
	int results_n;
	time_t stat_ts[BITFURY_STAT_N];
	unsigned int stat_counter;
	unsigned int future_nonce;
	unsigned int old_nonce;
	struct timespec timer1;
	struct timespec timer2;
	struct timespec otimer1;
	struct timespec otimer2;
	struct timespec predict1;
	struct timespec predict2;
	unsigned int counter1, counter2;
	unsigned int ocounter1, ocounter2;
	int rate; //per msec
	int osc_slow;
	int osc_fast;
	int req1_done, req2_done;
	double mhz;
	double ns;
	unsigned slot;
	unsigned fasync;
};

int libbitfury_readHashData(unsigned int *res);
extern void libbitfury_sendHashData1(int chip_id, struct bitfury_device *d, bool second_run);
void libbitfury_sendHashData(struct bitfury_device *bf, int chip_n);
void work_to_payload(struct bitfury_payload *p, struct work *w);
struct timespec t_diff(struct timespec start, struct timespec end);
extern void send_reinit(struct spi_port *, int slot, int chip_n, int n);
extern void send_freq(struct spi_port *, int slot, int chip_n, int bits);
extern int libbitfury_detectChips1(struct spi_port *);
extern int libbitfury_detectChips(struct spi_port *, struct bitfury_device *devices);
void libbitfury_shutdownChips(struct bitfury_device *devices, int chip_n);

#endif /* __LIBBITFURY_H__ */
