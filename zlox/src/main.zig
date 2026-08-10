const std = @import("std");
const Io = std.Io;

const zlox = @import("zlox");
const debug = zlox.debug;
const OpCode = zlox.chunk.OpCode;
const Chunk = zlox.chunk.Chunk;
const ZloxAllocator = zlox.mem.ZloxAllocator;
// const Value =

pub fn main(init: std.process.Init) !void {
    const io = init.io;

    var za = ZloxAllocator.init();
    const gpa = za.allocator();

    var chunk: Chunk = .init();
    defer chunk.deinit(gpa);
    const constant = try chunk.writeConstant(gpa, .{ .number = 1.2 });
    try chunk.writeCode(gpa, .op_constant, 1);
    try chunk.write(gpa, constant, 1);
    try chunk.writeCode(gpa, .op_return, 2);
    try debug.disassembleChunk(io, &chunk, "test chunk");
    return;
}
