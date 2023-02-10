// See LICENSE_CELLO file for license and copyright information

/// @file     parameters_ParameterAccessor.hpp
/// @author   Matthew Abruzzo (matthewabruzzo@gmail.com)
/// @date     Jan 17 2023
/// @brief    [\ref Parameters] Declaration for the ParameterAccessor class

#ifndef PARAMETERS_PARAMETER_ACCESSOR_HPP
#define PARAMETERS_PARAMETER_ACCESSOR_HPP

class ParameterAccessor {

  /// @class    ParameterAccessor
  /// @ingroup  Parameters
  /// @brief    [\ref Parameters] Acts as an interface for accessing parameters
  ///
  /// A lightweight wrapper around a Parameters object that provides access
  /// access to parameters stored by that object, which share a common root
  /// "parameter_path" (defined below). Instances of this class are intended
  /// to be used when initializing objects in other software components. The
  /// two guiding principles include:
  ///     1. restricting access to parameters within the associated root path
  ///        This is to discourage design of objects that are configured by
  ///        parameters scattered throughout the parameter file. In rare cases
  ///        (e.g. deprecating a parameter), exceptions need to be made. Thus,
  ///        an "escape-hatch" is provided to directly access the wrapped
  ///        Parameters object.
  ///     2. providing an explicit way to signal that  root-path's
  ///        name. This can be useful when multiple instances of the same class
  ///        (e.g. a Method class), but each instance has different
  ///        configurations.
  ///
  /// @par "parameter_path"
  /// Cello uses a "hierarchical" parameter file: the parameters themselves are
  /// essentially leaf nodes in a tree-hierarchy of "groups" (like how a file
  /// is organized in a directory hierarchy). A parameter_path unambiguously
  /// identifes a parameter in this hierarchy. A given parameter_path lists the
  /// names of ancestor "groups", separated by colons, and lists the name
  /// of the parameter at the end. An example parameter_path is
  /// ``"Method:null:dt"``
  ///
  /// @note
  /// alternative names for this class include ParameterClient, ParameterView,
  /// ParameterTerminal... They reflect the fact that the class provides access
  /// to the parameters held in a centralized Parameters object
public:

  /// construct a new ParameterAccessor object
  ParameterAccessor(Parameters &p, const std::string& root_parameter_path)
    : wrapped_p_(p),
      root_parameter_path_(root_parameter_path)
  {
    ASSERT("ParameterAccessor::ParameterAccessor",
           "root_parameter_path must not have a trailing colon",
           root_parameter_path.back() != ':');
  }

  // default implementations of copy and move constructors
  // (maybe we should delete these/make the private to prevent users from
  // storing them)
  ParameterAccessor(const ParameterAccessor&) = default;
  ParameterAccessor(ParameterAccessor&&) = default;

  // the following operations are deleted (because the class holds a reference
  // and a const member as attributes)
  ParameterAccessor() = delete;
  ParameterAccessor& operator=(const ParameterAccessor&) = delete;
  ParameterAccessor& operator=(ParameterAccessor&&) = delete;

  /// query the root parameter path
  const std::string& get_root_parpath() const noexcept
  {return root_parameter_path_;}

  int value (std::string s, int deflt) noexcept
  { return value_integer(s,deflt); }
  double value (std::string s, double deflt) noexcept
  { return value_float(s,deflt); }
  bool value (std::string s, bool deflt) noexcept
  { return value_logical(s, deflt); }
  std::string value (std::string s, std::string deflt) noexcept
  { return value_string(s, deflt); }

  int value (int i,std::string s, int deflt) noexcept
  { return list_value_integer(i,s,deflt); }
  double value (int i,std::string s, double deflt) noexcept
  { return list_value_float(i,s,deflt); }
  bool value (int i,std::string s, bool deflt) noexcept
  { return list_value_logical(i,s,deflt); }
  std::string value (int i,std::string s, const char * deflt) noexcept
  { return list_value_string(i,s,deflt); }
  std::string value (int i,std::string s, std::string deflt) noexcept
  { return list_value_string(i,s,deflt); }

  /// Return the type of the given parameter
  parameter_type type(std::string param) noexcept;

  /// Return the Param pointer for the specified parameter
  Param * param (std::string parameter);

  /// Return the integer-valued parameter
  int value_integer (std::string s, int deflt = 0) noexcept;
  /// Return the floating-point valued parameter
  double value_float (std::string s, double deflt = 0.0) noexcept;
  /// Return the logical-valued parameter
  bool value_logical (std::string s, bool deflt = false) noexcept;
  /// Return the string-valued parameter
  std::string value_string ( std::string s, std::string deflt = "") noexcept;

  /// Return the length of the list parameter
  int list_length (std::string parameter);
  /// Access an integer list element
  int list_value_integer (int i, std::string s, int deflt = 0) noexcept;
  /// Access a floating point list element
  double list_value_float (int i, std::string s, double deflt = 0.0) noexcept;
  /// Access a logical list element
  bool list_value_logical (int i, std::string s, bool deflt = false) noexcept;
  /// Access a string list element
  std::string list_value_string (int, std::string, std::string d="") noexcept;

  /// Return the full name of the parameter (including the root parameter path)
  std::string full_name(const std::string& parameter) const noexcept
  { return root_parameter_path_ + ":" + parameter; }

  /// Only use in case of emergencies
  Parameters& wrapped_Parameters_ref() noexcept { return wrapped_p_; }

  /// Returns a vector holding the names of all leaf parameters that share the
  /// root parameter path encapsulated by this object
  std::vector<std::string> leaf_parameter_names() const noexcept
  { return wrapped_p_.leaf_parameter_names(root_parameter_path_); }

private:

  std::vector<std::string> pop_wrapped_p_groups_()
  {
    const int n = wrapped_p_.group_depth();
    std::vector<std::string> grps(n);
    for (int i = 0; i < n; i++) { grps[i] = wrapped_p_.group(i); }
    wrapped_p_.group_clear();
    return grps;
  }

  void restore_wrapped_p_groups_(const std::vector<std::string>& groups)
  {
    wrapped_p_.group_clear();
    for (const std::string& grp : groups) { wrapped_p_.group_push(grp); }
  }

private: // attributes
  /// the wrapped Parameters object
  ///
  /// the Parameters object is implicitly assumed to outlive the instance
  /// holding this reference
  Parameters &wrapped_p_;

  /// The associated root parameter path.
  ///
  /// This will never have a trailing colon.
  ///
  /// An invariant of this class is that this will NOT change. If we're ever
  /// tempted to allow this attribute to change, we should prefer creation of a
  /// new ParameterAccessor instance (since they are light)
  const std::string root_parameter_path_;
};

#endif /* PARAMETERS_PARAMETER_ACCESSOR_HPP */
