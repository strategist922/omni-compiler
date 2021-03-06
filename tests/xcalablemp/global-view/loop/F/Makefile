XFC     = xmpf90
XRUN    = mpiexec
TESTS = $(wildcard *.f90)
EXES  = $(TESTS:.f90=.x)
OBJS  = $(TESTS:.f90=.o)

.PHONY: clean all default run submit showlog cleanlog

all default: $(EXES)

.SUFFIXES: .x .f90

.f90.x:
	$(XFC) -o $@ $<

run: $(EXES)
	$(XRUN) -n 2 ./292.x
	$(XRUN) -n 2 ./315_loop.x
	$(XRUN) -n 2 ./360_arrayAsign.x
	$(XRUN) -n 4 ./reduction_iand.x
	$(XRUN) -n 4 ./reduction_ieor.x
	$(XRUN) -n 4 ./reduction_ior.x
	$(XRUN) -n 4 ./reduction_max.x
	$(XRUN) -n 4 ./reduction_min.x
	$(XRUN) -n 4 ./reduction_mult.x
	$(XRUN) -n 4 ./reduction_plus.x
	$(XRUN) -n 4 ./gblock.x
	$(XRUN) -n 8 ./reduction_iand2.x
	$(XRUN) -n 8 ./reduction_ieor2.x
	$(XRUN) -n 8 ./reduction_ior2.x
	$(XRUN) -n 8 ./reduction_max2.x
	$(XRUN) -n 8 ./reduction_min2.x
	$(XRUN) -n 8 ./reduction_mult2.x
	$(XRUN) -n 16 ./reduction_plus3.x
	$(XRUN) -n 16 ./gblock2.x
	$(XRUN) -n 2 ./different_template.x
	$(XRUN) -n 1 ./387_l2g.x

RUN:
	mkdir RUN

RUN/%.x:: %.x
	cp $< $@

RUN/go.sh: go.template Makefile
	cp $< $@ && grep XRUN Makefile | sed -e 's/(XRUN)/{XRUN}/' -e 's/ *= */=/' | grep -v Makefile >>$@

submit: all RUN RUN/go.sh $(EXES:%=RUN/%)
	cd RUN; pjsub go.sh

showlog:
	cat RUN/go.sh.e* RUN/go.sh.o*

cleanlog:
	rm -rf RUN

clean: cleanlog
	rm -f $(EXES) $(OBJS)

