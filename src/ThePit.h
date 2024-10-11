#ifndef THE_PIT_H
#define THE_PIT_H

// CKA_TODO: Implement different printf
#define DBG_LOGF(...) printf(__VA_ARGS__)
#define DBG_BREAKPOINT() DebugBreak()
#define THE_PIT_ASSERT(Expr) \
	if (!(Expr)) \
	{ \
		DBG_LOGF("ASSERT FAILED!\n\tExpression: %s\n\tFile: %s, Line: %d\n", #Expr, __FILE__, __LINE__); \
	}
#define THE_PIT_UNUSED(Var) (void)Var

#endif // THE_PIT_H
