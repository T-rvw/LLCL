#pragma once

// Namespace
#ifndef LLCL_NAME
	// No namespace by default.
	#define LLCL_NAMESPACE_BEGIN
	#define LLCL_NAMESPACE_END
#else
	// Use customized name for namespace.
	#define LLCL_NAMESPACE_BEGIN \
		namespace LLCL_NAME \
		{

	#define LLCL_NAMESPACE_END \
		}
#endif

#define NAME_PREFIX_NAMESPACE(v) LLCL_NAME##::v