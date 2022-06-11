#pragma once

#include <string>

typedef struct FunctionInfoBase {
  std::string name;
  std::string return_type;
  std::string signature;
  std::vector<std::string> parameters;
  std::vector<std::string> scope;
  bool is_noexcept = false;
  bool is_constexpr = false;
  bool is_consteval = false;
  bool is_variadic = false;
  bool is_deleted = false;

  /**
   * @brief operator== for overload check
   *
   * @param rhs rgiht hand side
   * @return true
   * @return false
   *
   * @details see https://stackoverflow.com/questions/9568852/overloading-by-return-type
   */
  bool operator== (const FunctionInfoBase &rhs) const noexcept {
    return (name == rhs.name
      && parameters == rhs.parameters
      && scope == rhs.scope
    );
  }

  bool InScopeOf(const std::vector<std::string> &rhs_scope) const noexcept {
    return scope.size() >= rhs_scope.size()
      && std::equal(rhs_scope.begin(), rhs_scope.end(), scope.begin());
  }
} FunctionBase;

/**
 * @brief Member Function Info
 *
 */
typedef struct MemberFunctionInfo {
  enum class AccessSpecifier : int {
    kPublic,
    kPrivate,
    kProtected
  };
  FunctionInfoBase base;
  std::string class_name;
  enum AccessSpecifier access_specifier;
  bool is_const = false;
  bool is_volatile = false;
  bool is_polymorphic = false;  /// virtual, override or final
  std::vector<std::string> base_classes;

  bool operator== (const MemberFunctionInfo &rhs) const noexcept {
    return (base == rhs.base
      && class_name == rhs.class_name
      && is_const == rhs.is_const
      && is_volatile == rhs.is_volatile
    );
  }

  bool InScopeOf(const std::vector<std::string> &rhs_scope) const noexcept {
    return base.InScopeOf(rhs_scope);
  }
} MemberFunctionInfo;

/**
 * @brief Function Info
 *
 */
typedef struct FunctionInfo {
  FunctionInfoBase base;
  bool is_extern = false;
  bool is_static = false;

  bool operator== (const FunctionInfo &rhs) const noexcept {
    return (base == rhs.base
    );
  }

  bool InScopeOf(const std::vector<std::string> &rhs_scope) const noexcept {
    return base.InScopeOf(rhs_scope);
  }
} FunctionInfo;
