

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//
// A method to access memory-mapped peripherals
//

typedef uint32_t u32;

struct axi_regs {
	u32 reserved[3];
	u32 is; /* 0xC: Interrupt status */
	u32 reserved2;
	u32 ie; /* 0x14: Interrupt enable */
	u32 reserved3[251];
	u32 rcw1; /* 0x404: Rx Configuration Word 1 */
	u32 tc; /* 0x408: Tx Configuration */
	u32 reserved4;
	u32 emmc; /* 0x410: EMAC mode configuration */
	u32 reserved5[59];
	u32 mdio_mc; /* 0x500: MII Management Config */
	u32 mdio_mcr; /* 0x504: MII Management Control */
	u32 mdio_mwd; /* 0x508: MII Management Write Data */
	u32 mdio_mrd; /* 0x50C: MII Management Read Data */
	u32 reserved6[124];
	u32 uaw0; /* 0x700: Unicast address word 0 */
	u32 uaw1; /* 0x704: Unicast address word 1 */
};


u32* data;


#define readw(addr) (*(volatile unsigned int *)(addr))

int main(){
    int i;
    int size;   
    struct axi_regs *regs; 
    size = sizeof(struct axi_regs);
    data = (u32 *)malloc(size);
    printf("size        : %d\n",size);
    printf("data address: %08x\n",data);
    for(i=0;i<size/4;i++) {
        *(data+i) = i*2+1; 
    }
	regs = (struct axi_regs *)(data);
    printf(" data[3] address : %08x \n",data+3);
    printf(" data[3]         : %08x \n",*(data+3));

#ifdef __mips__
    __asm__ (".set noreorder");
    __asm__ ("ssnop");
#endif

    printf(" regs.is address : %08x \n",&regs->is);

#ifdef __mips__
    __asm__ ("ssnop");
#endif

    printf(" regs.is         : %08x \n",readw(&regs->is));

#ifdef __mips__
    __asm__ (".set reorder");
    __asm__ ("ssnop");
#endif

    return 0;
}
