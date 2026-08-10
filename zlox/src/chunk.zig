const std = @import("std");
const ArrayList = std.ArrayList;
const Allocator = std.mem.Allocator;

const valueLib = @import("value.zig");
const Value = valueLib.Value;
const ValueArray = valueLib.ValueArray;

pub const OpCode = enum(u8) {
    op_constant,
    op_return,
};

pub const Chunk = struct {
    code: ArrayList(u8),
    constants: ValueArray,
    lines: ArrayList(LineInfo),

    pub fn init() Chunk {
        return .{
            .code = .empty,
            .constants = .init(),
            .lines = .empty,
        };
    }

    pub fn write(self: *Chunk, za: Allocator, byte: u8, line: u16) !void {
        if (self.lines.items.len > 0 and self.lines.getLast().line == line) {
            self.lines.items[self.lines.items.len - 1].count += 1;
        } else {
            try self.lines.append(za, .{ .line = line, .count = 1 });
        }
        return self.code.append(za, byte);
    }

    pub fn writeCode(self: *Chunk, za: Allocator, code: OpCode, line: u16) !void {
        return self.write(za, @intFromEnum(code), line);
    }

    pub fn writeConstant(self: *Chunk, za: Allocator, value: Value) !u8 {
        return @intCast(try self.constants.write(za, value));
    }

    pub fn getLine(self: *const Chunk, index: usize) u16 {
        var result: u16 = 0;
        var idx: usize = 0;
        for (self.lines.items) |lineinfo| {
            idx += @intCast(lineinfo.count);
            if (index < idx) {
                result = lineinfo.line;
                break;
            }
        }
        return result;
    }

    pub fn deinit(self: *Chunk, za: Allocator) void {
        self.code.deinit(za);
        self.constants.deinit(za);
        self.lines.deinit(za);
        self.code = .empty;
    }
};

const LineInfo = struct {
    line: u16,
    count: u16,
};
