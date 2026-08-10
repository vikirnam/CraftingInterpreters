const std = @import("std");
const Allocator = std.mem.Allocator;
const ArrayList = std.ArrayList;

pub const ValueType = enum {
    number,
};

pub const Value = union(ValueType) {
    number: f64,
};

pub const ValueArray = struct {
    inner: ArrayList(Value),

    pub fn init() ValueArray {
        return .{
            .inner = .empty,
        };
    }

    pub fn write(va: *ValueArray, za: Allocator, value: Value) !usize {
        try va.inner.append(za, value);
        return va.inner.items.len - 1;
    }

    pub fn deinit(va: *ValueArray, za: Allocator) void {
        va.inner.deinit(za);
    }
};
