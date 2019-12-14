#include <postgres.h>
#include <fmgr.h>
#include <libpq/pqformat.h>
#include <math.h>

#ifdef PG_MODULE_MAGIC
	PG_MODULE_MAGIC;
#endif

typedef struct
{
	double x, y;
} point;

PG_FUNCTION_INFO_V1(point_in);
PG_FUNCTION_INFO_V1(point_out);

PG_FUNCTION_INFO_V1(point_recv);
PG_FUNCTION_INFO_V1(point_send);

Datum point_in(PG_FUNCTION_ARGS)
{
	char *s = PG_GETARG_CSTRING(0);

	point *v = (point*)palloc(sizeof(point));

	if (sscanf(s, "(%lf,%lf)", &(v->x), &(v->y)) != 2)
	{
		ereport(ERROR, (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION), errmsg("Invalid input syntax for point: \"%s\"", s)));
	}

	PG_RETURN_POINTER(v);
}

Datum point_out(PG_FUNCTION_ARGS)
{
	point *v = (point*)PG_GETARG_POINTER(0);

	char *s = (char*)palloc(100);

	snprintf(s, 100, "(%lf,%lf)", v->x, v->y);

	PG_RETURN_CSTRING(s);
}

Datum point_recv(PG_FUNCTION_ARGS)
{
	StringInfo buffer = (StringInfo)PG_GETARG_POINTER(0);

	point *v = (point*)palloc(sizeof(point));

	v->x = pq_getmsgfloat8(buffer);
	v->y = pq_getmsgfloat8(buffer);

	PG_RETURN_POINTER(v);
}

Datum point_send(PG_FUNCTION_ARGS)
{
	point *v = (point*)PG_GETARG_POINTER(0);

	StringInfoData buffer;

	pq_begintypsend(&buffer);

	pq_sendfloat8(&buffer, v->x);
	pq_sendfloat8(&buffer, v->y);

	PG_RETURN_BYTEA_P(pq_endtypsend(&buffer));
}
