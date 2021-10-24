#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define FILE_AUTOOPEN 0

#define CANVAS_WIDTH 120
#define CANVAS_HEIGHT 40

typedef uint8_t canvas_t[CANVAS_HEIGHT][CANVAS_WIDTH];

int imin(int a, int b);
int imax(int a, int b);
int iclamp(int value, int lo, int hi);
float fradius2(float x, float y);

char color_to_char(uint8_t color);

void canvas_fill(canvas_t canvas, uint8_t c);

void canvas_draw_point(canvas_t canvas, int x, int y, uint8_t c);
void canvas_draw_hline(canvas_t canvas, int x1, int x2, int y, uint8_t c);
void canvas_draw_vline(canvas_t canvas, int x, int y1, int y2, uint8_t c);
void canvas_draw_rect(canvas_t canvas, int x1, int x2, int y1, int y2, uint8_t c);
void canvas_draw_circle(canvas_t canvas, int cx, int cy, float radius, uint8_t c);

void canvas_print(canvas_t canvas);
int canvas_write_ascii(canvas_t canvas, FILE* stream);
int canvas_write_ppm6(canvas_t canvas, FILE* stream);

void draw_my_image(canvas_t canvas);

int main(void)
{
	canvas_t canvas = {0};
	draw_my_image(canvas);
	canvas_print(canvas);

	const char filename[] = "data/img.ppm";
	FILE* file = fopen(filename, "wb");
	if (!file)
	{
		fprintf(stderr, "Error: Failed to open file %s!\n", filename);
		return EXIT_FAILURE;
	}

	// canvas_write_ascii(canvas, file);
	canvas_write_ppm6(canvas, file);

	fclose(file);

#if FILE_AUTOOPEN && defined(__linux__)
	char xdg_command[128] = {0};
	snprintf(xdg_command, sizeof(xdg_command), "xdg-open %s", filename);
	system(xdg_command);
#endif

	return EXIT_SUCCESS;
}

int imin(int a, int b)
{
	return a < b ? a : b;
}

int imax(int a, int b)
{
	return a < b ? b : a;
}

int iclamp(int value, int lo, int hi)
{
	return value < lo ? lo
		: value > hi ? hi
		: value;
}

float fradius2(float x, float y)
{
	return x * x + y * y;
}

char color_to_char(uint8_t color)
{
	if (color < 32)
		return ' ';
	if (color < 64)
		return '.';
	if (color < 96)
		return ':';
	if (color < 128)
		return '=';
	if (color < 160)
		return '?';
	if (color < 192)
		return '%';
	if (color < 224)
		return 'H';
	return '@';
}

void canvas_fill(canvas_t canvas, uint8_t c)
{
	for (uint8_t *p = &canvas[0][0]; p != &canvas[0][0] + CANVAS_HEIGHT * CANVAS_WIDTH; ++p)
	{
		*p = c;
	}
}

void canvas_draw_point(canvas_t canvas, int x, int y, uint8_t c)
{
	if (0 < x && x < CANVAS_WIDTH && 0 < y && y < CANVAS_HEIGHT)
	{
		canvas[y][x] = c;
	}
}

void canvas_draw_hline(canvas_t canvas, int x1, int x2, int y, uint8_t c)
{
	x1 = iclamp(x1, 0, CANVAS_WIDTH - 1);
	x2 = iclamp(x2, 0, CANVAS_WIDTH - 1);
	y = iclamp(y, 0, CANVAS_HEIGHT - 1);
	for (int x = x1; x <= x2; ++x)
	{
		canvas[y][x] = c;
	}
}

void canvas_draw_vline(canvas_t canvas, int x, int y1, int y2, uint8_t c)
{
	x = iclamp(x, 0, CANVAS_WIDTH - 1);
	y1 = iclamp(y1, 0, CANVAS_HEIGHT - 1);
	y2 = iclamp(y2, 0, CANVAS_HEIGHT - 1);
	for (int y = y1; y <= y2; ++y)
	{
		canvas[y][x] = c;
	}
}

void canvas_draw_rect(canvas_t canvas, int x1, int x2, int y1, int y2, uint8_t c)
{
	x1 = iclamp(x1, 0, CANVAS_WIDTH - 1);
	x2 = iclamp(x2, 0, CANVAS_WIDTH - 1);
	y1 = iclamp(y1, 0, CANVAS_HEIGHT - 1);
	y2 = iclamp(y2, 0, CANVAS_HEIGHT - 1);
	for (int y = y1; y <= y2; ++y)
	{
		for (int x = x1; x <= x2; ++x)
		{
			canvas[y][x] = c;
		}
	}
}

void canvas_draw_circle(canvas_t canvas, int cx, int cy, float radius, uint8_t c)
{
	const int x_min = iclamp((int)floorf((float)cx - radius), 0, CANVAS_WIDTH - 1);
	const int x_max = iclamp((int)ceilf((float)cx + radius), 0, CANVAS_WIDTH - 1);
	const int y_min = iclamp((int)floorf((float)cy - radius), 0, CANVAS_HEIGHT - 1);
	const int y_max = iclamp((int)ceilf((float)cy + radius), 0, CANVAS_HEIGHT - 1);

	for (int y = y_min; y <= y_max; ++y)
	{
		for (int x = x_min; x <= x_max; ++x)
		{
			if (fradius2((float)(x - cx), (float)(y - cy)) <= radius * radius)
			{
				canvas[y][x] = c;
			}
		}
	}
}

void canvas_print(canvas_t canvas)
{
	for (int row = 0; row < CANVAS_HEIGHT; ++row)
	{
		for (int col = 0; col < CANVAS_WIDTH; ++col)
		{
			putchar(color_to_char(canvas[row][col]));
		}
		putchar('\n');
	}
}

int canvas_write_ascii(canvas_t canvas, FILE* stream)
{
	for (int row = 0; row < CANVAS_HEIGHT; ++row)
	{
		for (int col = 0; col < CANVAS_WIDTH; ++col)
		{
			if (fputc(color_to_char(canvas[row][col]), stream) == EOF)
			{
				fprintf(stderr, "Error in canvas_write_ascii(..): %s", strerror(errno));
				return -1;
			}
		}
		if (fputc('\n', stream) == EOF)
		{
			fprintf(stderr, "Error in canvas_write_ascii(..): %s", strerror(errno));
			return -1;
		}
	}
	return 1;
}

int canvas_write_ppm6(canvas_t canvas, FILE* stream)
{
	fprintf(stream, "P6\n%d %d\n255\n", CANVAS_WIDTH, CANVAS_HEIGHT);
	for (int row = 0; row < CANVAS_HEIGHT; ++row)
	{
		for (int col = 0; col < CANVAS_WIDTH; ++col)
		{
			const uint8_t grey = canvas[row][col];
			const uint8_t rgb[3] = {grey, grey, grey};
			const size_t count = sizeof(rgb) / sizeof(rgb[0]);
			if (fwrite(rgb, sizeof(rgb[0]), count, stream) != count)
			{
				fprintf(stderr, "Error in canvas_write_ppm6(..): %s", strerror(errno));
				return -1;
			}
		}
	}
	return 1;
}

void draw_my_image(canvas_t canvas)
{
	canvas_fill(canvas, 35);

	const int num_stripes = 5;
	int prev_stripe_y = 0;
	for (int i = 0; i < num_stripes; ++i)
	{
		const float ratio = ((float)(i + 1)) / ((float)num_stripes);
		const int next_stripe_y = (int)floorf(ratio * CANVAS_HEIGHT);
		canvas_draw_rect(canvas, 0, CANVAS_WIDTH - 1, prev_stripe_y, next_stripe_y - 1, (uint8_t)(ratio * 255));
		prev_stripe_y = next_stripe_y;
	}
	canvas_draw_circle(canvas, 20, 20, 10.7f, 50);
	canvas_draw_point(canvas, 20, 20, 255);

	canvas_draw_circle(canvas, 60, 20, 10.7f, 220);
	canvas_draw_point(canvas, 60, 20, 35);

	canvas_draw_circle(canvas, 100, 20, 10.7f, 255);
	canvas_draw_point(canvas, 100, 20, 120);
}
