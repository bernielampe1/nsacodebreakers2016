
$(BUILD_DIR)/libseh.a: $(OBJS)
	$(AR) rs $@ $^

$(BUILD_DIR)/%.o: os/$(OSNAME)/arch/$(ARCHNAME)/%.s
	$(CC) $(ASFLAGS) -o $@ -c $^

$(BUILD_DIR)/%.o: os/$(OSNAME)/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILD_DIR)/%.o: common/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILD_DIR)/%.o: common/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGETS)

