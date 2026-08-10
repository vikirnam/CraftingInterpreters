const std = @import("std");

const Chunk = @import("chunk.zig").Chunk;
const OpCode = @import("chunk.zig").OpCode;
const Value = @import("value.zig").Value;

const Writer = std.Io.Writer;

pub fn disassembleChunk(io: std.Io, chunk: *const Chunk, name: []const u8) !void {
    var buffer: [4096]u8 = undefined;
    var writer = std.Io.File.stdout().writerStreaming(io, &buffer);
    var stdout = &writer.interface;

    try stdout.print("== {s}  ==\n", .{name});

    var offset: u32 = 0;
    while (offset < chunk.code.items.len) {
        offset = try disassembleInstruction(stdout, chunk, offset);
    }

    try stdout.flush();
}

fn disassembleInstruction(stdout: *Writer, chunk: *const Chunk, offset: u32) !u32 {
    try stdout.print("{d:0>4} ", .{offset});
    if (offset > 0 and chunk.getLine(offset) == chunk.getLine(offset - 1)) {
        try stdout.print("   | ", .{});
    } else {
        try stdout.print("{d:4} ", .{chunk.getLine(offset)});
    }

    const op: OpCode = @enumFromInt(chunk.code.items[offset]);
    switch (op) {
        .op_return => return simpleInstruction(stdout, "OP_RETURN", offset),
        .op_constant => return constantInstruction(stdout, "OP_CONSTANT", chunk, offset),
    }
}

fn simpleInstruction(stdout: *Writer, name: []const u8, offset: u32) !u32 {
    try stdout.print("{s}\n", .{name});
    return offset + 1;
}

fn constantInstruction(
    stdout: *Writer,
    name: []const u8,
    chunk: *const Chunk,
    offset: u32,
) !u32 {
    const constant = chunk.code.items[offset + 1];
    try stdout.print("{s:<16} {d:4} '", .{ name, constant });
    try printValue(stdout, chunk.constants.inner.items[constant]);
    try stdout.print("'\n", .{});
    return offset + 2;
}

fn printValue(stdout: *Writer, value: Value) !void {
    switch (value) {
        .number => |n| try stdout.print("{}", .{n}),
    }
}
