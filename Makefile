LD = $(shell which g++)
CXX = $(shell which g++)

override CXXFLAGS += -Wall

EXE = Project3.out
OBJS = driver.o Song.o Library.o TitleCompare.o AlbumCompare.o ArtistCompare.o GenreCompare.o YearCompare.o

DEPS = $(addprefix.,$(OBJS:.o=.d))

$(EXE): $(DEPS) $(OBJS)
	$(LD) $(LDFLAGS) $(LDLIBS) $(OBJS) -o $@

.%.d: %.cpp
	@$(RM) $@; \
	$(CXX) -MM -MF $@ -MT "$(<:.cpp=.o) $@" -c $(CPPFLAGS) $<

$(OBJS): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS) $(EXE)
.PHONY: run
run: $(EXE)
	./$(EXE) $(LIBRARY_FILE)
