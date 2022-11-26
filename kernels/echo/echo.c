#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#define COM_RX		0x1000	// In:  Receive buffer (DLAB=0)
#define COM_LSR		0x1014	// In:  Line Status Register
#define COM_LSR_DATA	0x01	// Data available

#define COM1		0x1fe00000

int main(const char *args) {
	int c = '\0';
	while (1) {
		while (*(volatile uint32_t *)(COM1 + COM_LSR) & COM_LSR_DATA) {
			c = *(volatile uint32_t *)(COM1 + COM_RX);
			printf("get char: %d ", c);
			if (c == '\r' || c == '\n') {
				putch('\r');
				putch('\n');
			} else if (c == '\b' || c == 127) {
				putch('\b');
				putch(' ');
				putch('\b');
			} else {
				putch(c);
			}
			putch('\n');
			putch('\r');
		}
		/* press 'q' to exit */
		if (c == 'q')
			break;
	}
	return 0;
}
