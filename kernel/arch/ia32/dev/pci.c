/*  This file is part of The Firekylin Operating System.
 *
 *  Copyright 2016 Liuxiaofeng
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <firekylin/kernel.h>
#include <firekylin/pci.h>

#define MAX_PCI_DEVICE		32

static int pci_count;
static struct pci_device pci_table[MAX_PCI_DEVICE];

/*
 * only scan the 0 bus.
 */
void pci_init(void)
{
	char bus = 0;
	char slot;
	char func;
	pci_dev_t tmp_pci_dev;
	unsigned short vendor_id;

	for (slot = 0; slot < 32; slot++) {
		for (func = 0; func < 8; func++) {
			tmp_pci_dev = pci_dev(bus, slot, func);
			vendor_id = pci_read_config_word(tmp_pci_dev, 0);
			if (vendor_id == 0xffff)
				continue;

			pci_table[pci_count].dev = tmp_pci_dev;
			int *p = (int *) &(pci_table[pci_count].vendor_id);

			for (int i = 0; i < 64; i += 4) {
				*p++ = pci_read_config(tmp_pci_dev, i);
			}

			pci_count++;
			if (pci_count >= MAX_PCI_DEVICE) {
				printk("there are too many devices, skip\n");
				return;
			}
		}
	}
}

void dump_pci(void)
{
	for (int i = 0; i < pci_count; i++) {
		printk("%x  %x  %x \n", pci_table[i].dev,
			pci_table[i].vendor_id, pci_table[i].device_id);
	}
}

struct pci_device *pci_find_device(unsigned short vendor, unsigned short device)
{
	struct pci_device *pci = pci_table;
	for (int i = 0; i < pci_count; i++) {
		if ((vendor == pci->vendor_id) && (device == pci->device_id))
			return pci;
		pci++;
	}
	return NULL;
}
