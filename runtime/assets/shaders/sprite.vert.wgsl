struct VertexInput {
    @location(0) position: vec2<f32>,
    @location(1) uv: vec2<f32>,
    @location(2) color: u32,
    @location(3) tex_index: u32,
}

struct VertexOutput {
    @builtin(position) position: vec4<f32>,
    @location(0) uv: vec2<f32>,
    @location(1) color: vec4<f32>,
    @location(2) tex_index: u32,
}

struct Uniforms {
    projection: mat4x4<f32>,
}

@group(0) @binding(0) var<uniform> uniforms: Uniforms;

@vertex
fn main(input: VertexInput) -> VertexOutput {
    var output: VertexOutput;
    output.position = uniforms.projection * vec4<f32>(input.position, 0.0, 1.0);
    output.uv = input.uv;

    let c = input.color;
    output.color = vec4<f32>(
        f32((c >> 0) & 0xFF) / 255.0,
        f32((c >> 8) & 0xFF) / 255.0,
        f32((c >> 16) & 0xFF) / 255.0,
        f32((c >> 24) & 0xFF) / 255.0,
    );
    output.tex_index = input.tex_index;
    return output;
}