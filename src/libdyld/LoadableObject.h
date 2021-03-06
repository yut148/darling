#ifndef LOADABLEOBJECT_H
#define LOADABLEOBJECT_H
#include <dlfcn.h>
#include <string>
#include <atomic>
#include "dyld_priv.h"

namespace Darling {

class MachOObject;

class LoadableObject
{
protected:
	LoadableObject();
	virtual ~LoadableObject() {}
public:
	virtual void load() = 0;
	virtual void unload() = 0;
	virtual bool isLoaded() const = 0;
	
	virtual void* getExportedSymbol(const std::string& symbolName, bool nonWeakOnly = false) const = 0;
	virtual bool findSymbolInfo(const void* addr, Dl_info* p) const = 0;

	// This must return const char* because of a couple of NS* functions
	virtual const char* name() const = 0;

	// Absolute path to this object
	virtual const std::string& path() const = 0;

	// Minimum address loaded by this object
	virtual void* baseAddress() const = 0;

	// Stuf to do when libsystem's exit() is called
	virtual void atExit() {};
	
	int addRef();
	int delRef();
	inline int refCount() const { return m_refs; }

	// Whether exports of this object should be available for symbol resolution of subsequently loaded libraries (RTLD_GLOBAL)
	inline void setGlobalExports(bool global) { m_globalExports = global; }
	bool globalExports() const { return m_globalExports; }

	// Whether all lazy references should be bound upon loading.
	// Setting this to true is equivatent to using RTLD_NOW.
	inline void setBindAllAtLoad(bool bindAll) { m_bindAllAtLoad = bindAll; }
	inline bool bindAllAtLoad() const { return m_bindAllAtLoad; }

	inline void setNoDelete(bool noDelete) { m_noDelete = noDelete; }
	inline bool noDelete() const { return m_noDelete; }
	
	static LoadableObject* instantiateForPath(const std::string& path, MachOObject* requester, int flag = 0);

	inline dyld_image_states state() const { return m_state; }
protected:
	void transitionState(dyld_image_states newState);
protected:
	std::atomic<int> m_refs;
	bool m_globalExports = true;
	bool m_bindAllAtLoad = false, m_noDelete = false;
	dyld_image_states m_state;
};

} // namespace Darling

#endif
