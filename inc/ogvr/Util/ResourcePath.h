/** @file
    @brief Header

    @date 2014

    @author
    Ryan Pavlik
    <ryan@sensics.com>
    <http://sensics.com>

*/

// Copyright 2014 Sensics, Inc.
//
// All rights reserved.
//
// (Final version intended to be licensed under
// the Apache License, Version 2.0)

#ifndef INCLUDED_ResourcePath_h_GUID_00432A94_11D2_47B4_7493_4F66E635FBE2
#define INCLUDED_ResourcePath_h_GUID_00432A94_11D2_47B4_7493_4F66E635FBE2

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <string>
#include <vector>
#include <cstddef>

namespace ogvr {
namespace util {
    class ResourcePath;

    /** @brief Class representing a host and resource path in the OGVR logical
       system.

        Instances of this class always refer to an absolute path, with host and
       full
       path from the root. No assertions are made that the path is meaningful.

        Paths are essentially URLs, and follow the same rules. Canonical form of
       ResourcePaths does not end in a slash, and usage of the `.` and `..`
       pseudo-entries (for current directory and parent directory) is not
       supported
       for simplicity and security.

        Paths are immutable: navigating functions return a new ResourcePath.

        Enumeration ("browsing") is out of scope for this class - it may be
       supported in some cases by other code.
    */
    class ResourcePath {
      public:
        /// @brief Default constructor - initializes to ogvr://localhost/ (root)
        ResourcePath();

        /// @brief Constructs from a URL string.
        explicit ResourcePath(std::string const &url);

        /// @overload
        explicit ResourcePath(const char *url);

        /// @brief Go to parent path.
        ///
        /// If at the root on a host, this is a no-op
        ResourcePath GetParent() const;

        /// @brief Go to the named child. The name may include slashes for
        /// multiple
        /// levels.
        ResourcePath GetChild(std::string const &childName) const;

        /// @overload
        /// Does not take ownership of the argument.
        ResourcePath GetChild(const char *childName) const;

        /// @name Base Portion String Accessors
        /// At any time, "ogvr://" + GetHostString() + GetPathString()
        /// is the canonical form of a path.
        /// @{
        /// @brief Gets the entire path as a string.
        std::string GetString() const;

        /// @brief Gets the host portion of the path as a string
        std::string GetHostString() const;

        /// @brief Gets the path following the hostname as a string, starting
        /// with a
        /// leading slash.
        std::string GetPathString() const;
        /// @}

        /// @name Component-wise Accessors
        /// @{
        /// @brief Gets the number of named components. A path at the root
        /// is defined to have depth 0.
        std::size_t GetDepth() const;

        /// @brief Gets the identified component, where 0 is the name of
        /// the component immediately under the root.
        ///
        /// @precondition i < GetDepth()
        /// @throws std::out_of_range if precondition violated.
        std::string GetComponent(std::size_t i) const;
        /// @}

      private:
        std::string m_host;
        std::string m_path;
        typedef std::vector<std::size_t> IndexArray;
        IndexArray m_components;
    };
} // namespace util
} // namespace ogvr

#endif // INCLUDED_ResourcePath_h_GUID_00432A94_11D2_47B4_7493_4F66E635FBE2
