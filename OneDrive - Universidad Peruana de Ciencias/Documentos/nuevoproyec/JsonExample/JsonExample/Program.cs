using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

var builder = WebApplication.CreateBuilder(args);

// Configuración de servicios
builder.Services.AddControllers()
    .AddJsonOptions(options =>
    {
        // Configuración de serialización
        options.JsonSerializerOptions.PropertyNamingPolicy = JsonNamingPolicy.CamelCase;
        options.JsonSerializerOptions.DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull;
    });

var app = builder.Build();

// Middleware personalizado para logging
app.Use(async (context, next) =>
{
    Console.WriteLine($"➡️ Request: {context.Request.Method} {context.Request.Path}");
    await next.Invoke();
    Console.WriteLine($"⬅️ Response: {context.Response.StatusCode}");
});

// Middleware para manejo de errores
app.Use(async (context, next) =>
{
    try
    {
        await next.Invoke();
    }
    catch (Exception ex)
    {
        context.Response.StatusCode = 500;
        await context.Response.WriteAsync($"Error interno: {ex.Message}");
    }
});

// Endpoints simples
app.MapGet("/api/usuario", () =>
{
    var usuario = new Usuario { Id = 1, Nombre = "Jeremías", Activo = true };
    return Results.Json(usuario);
});

app.MapPost("/api/usuario", async (HttpContext context) =>
{
    var usuario = await JsonSerializer.DeserializeAsync<Usuario>(context.Request.Body);
    return Results.Json(new { mensaje = "Usuario recibido", usuario });
});

app.Run();

// Modelo de datos
public class Usuario
{
    public int Id { get; set; }
    public required string Nombre { get; set; }
    public bool Activo { get; set; }
}
