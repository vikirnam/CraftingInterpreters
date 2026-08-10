const std = @import("std");
const builtin = @import("builtin");
const Allocator = std.mem.Allocator;
const Alignment = std.mem.Alignment;

const ZloxAllocator = @This();

var debug_allocator = std.heap.DebugAllocator(.{}).init;
child: Allocator,
is_debug: bool,

pub fn init() ZloxAllocator {
    if (builtin.os.tag == .wasi) return .{
        .child = std.heap.wasm_allocator,
        .is_debug = false,
    };
    return switch (builtin.mode) {
        .Debug, .ReleaseSafe => ZloxAllocator{
            .child = debug_allocator.allocator(),
            .is_debug = true,
        },
        .ReleaseFast, .ReleaseSmall => ZloxAllocator{
            .child = std.heap.smp_allocator,
            .is_debug = false,
        },
    };
}

pub fn deinit(self: *ZloxAllocator) void {
    if (self.is_debug) {
        const status = debug_allocator.deinit();
        if (status == .leak) {
            @panic("Memory Leak Detected");
        }
    }
    debug_allocator = undefined;
}

pub fn allocator(self: *ZloxAllocator) Allocator {
    return .{ .ptr = self, .vtable = &.{
        .alloc = alloc,
        .resize = resize,
        .remap = remap,
        .free = free,
    } };
}

pub fn alloc(
    ctx: *anyopaque,
    len: usize,
    alignment: Alignment,
    ret_addr: usize,
) ?[*]u8 {
    const self: *ZloxAllocator = @ptrCast(@alignCast(ctx));
    const result = self.child.rawAlloc(len, alignment, ret_addr);
    return result;
}

pub fn resize(
    ctx: *anyopaque,
    memory: []u8,
    alignment: Alignment,
    new_len: usize,
    ret_addr: usize,
) bool {
    const self: *ZloxAllocator = @ptrCast(@alignCast(ctx));
    const result = self.child.rawResize(memory, alignment, new_len, ret_addr);
    return result;
}

pub fn remap(
    ctx: *anyopaque,
    memory: []u8,
    alignment: Alignment,
    new_len: usize,
    ret_addr: usize,
) ?[*]u8 {
    const self: *ZloxAllocator = @ptrCast(@alignCast(ctx));
    const result = self.child.rawRemap(memory, alignment, new_len, ret_addr);
    return result;
}

pub fn free(
    ctx: *anyopaque,
    memory: []u8,
    alignment: Alignment,
    ret_addr: usize,
) void {
    const self: *ZloxAllocator = @ptrCast(@alignCast(ctx));
    const result = self.child.rawFree(memory, alignment, ret_addr);
    return result;
}
