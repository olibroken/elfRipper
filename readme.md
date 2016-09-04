#bytecode extractor for elf obj files

## usage:

* __attribute__((section(".customsec")))void customfunc() { return; }
* elfRipper main.o .customsec
