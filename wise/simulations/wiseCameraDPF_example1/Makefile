LOG_FILE	:= dpf_results.txt
LOG_PART_FILE	:= dpf_part_results.txt

PLOT_TAG	:= DPF
PLOT_PART_TAG	:= PART_DPF

all:
	Castalia -c General

clean:
	find . -maxdepth 1 -regex "./[0-9]+-[0-9]+.*" | xargs rm -rf
	rm -rf Castalia-Trace.txt targets_info.txt wise_debug_log.txt
	rm -rf node*_$(PLOT_TAG)*_plot_data.dat
	rm -rf node*_$(PLOT_PART_TAG)*_plot_data.dat
	rm -rf $(LOG_FILE) $(LOG_PART_FILE)

cleanall: clean
	rm -rf plot_$(PLOT_TAG)_*.eps
	rm -rf plot_$(PLOT_PART_TAG)_*.eps
