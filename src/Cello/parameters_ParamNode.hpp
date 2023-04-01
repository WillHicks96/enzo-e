// See LICENSE_CELLO file for license and copyright information

/// @file     parameters_ParamNode.hpp
/// @author   James Bordner (jobordner@ucsd.edu)
/// @date     Mon May 10 12:43:27 PDT 2010
/// @brief [\ref Parameters] Node for representing parameters in a
///           tree of groups / subgroups /parameters /values

#ifndef PARAMETERS_PARAM_NODE_HPP
#define PARAMETERS_PARAM_NODE_HPP

class ParamNode {

  /// @class    ParamNode
  /// @ingroup  Parameters
  /// @brief    [\ref Parameters] Node representing a subtree of parameters

public: // interface

  /// Constructor
  ParamNode(std::string name) throw()
    : name_(name),
      subnodes_()
  {};

  //----------------------------------------------------------------------
  // Big Five
  //----------------------------------------------------------------------

  /// Destructor
  ~ParamNode() throw()
  {
    for (std::pair<const std::string, ParamNode*>& key_val : subnodes_) {
      delete key_val.second;
    }
  };

  // No copy/move constructors or assignment operators:
  ParamNode(const ParamNode&) = delete;
  ParamNode(ParamNode&&) = delete;
  ParamNode & operator= (const ParamNode &) = delete;
  ParamNode & operator= (const ParamNode &&) = delete;

public: // interface

  /// CHARM++ Pack / Unpack function
  inline void pup (PUP::er &p)
  {
    TRACEPUP;
    // NOTE: change this function whenever attributes change

    p | name_;

    // pup std::map<std::string,ParamNode*> subnodes_ using arrays
    
    int n;
    if (p.isPacking()) {
      n = 0;
      for(auto it=subnodes_.begin(); it != subnodes_.end(); it++) {
	++n;
      }
      p | n;
      for(auto it=subnodes_.begin(); it != subnodes_.end(); it++) {
	std::string name = it->first;
	int l = name.size();
	char * array = new char[l];
	strncpy(array,name.c_str(),l);
	p | l;
	delete [] array;
	p | *it->second;
      }
    } else {
      p | n;
      for (int i=0; i<n; i++) {
	std::string name;
	ParamNode * node;
	int l;
	p | l;
	char * array = new char[l];
	name = array;
	delete [] array;
	node = new ParamNode(name);
	p | *node;
	subnodes_[name] = node;
      }	
    }
  }

  /// Return the node name
  std::string name() const {return name_;};

  /// Return the number of subgroups
  int size()
  {return subnodes_.size(); }

  /// Return the ith subgroup
  std::string subgroup (int group_index)
  {
    if (0 <= group_index && group_index < size()) {
      int i = 0;
      for (auto it_param =  subnodes_.begin();
	   it_param != subnodes_.end();
	   ++it_param,i++) {
	if (group_index == i) {
	  return it_param->first;
	}
      }
    }
    return "";
  };

  /// Return the given subnode, returning 0 if it doesn't exist
  ParamNode * subnode(std::string subgroup)
  {
    auto search = subnodes_.find(subgroup);
    return (search != subnodes_.end()) ? search->second : nullptr;
  }

  /// Return the given subgroup, creating a new one if it doesn't exist
  ParamNode * new_subnode(std::string subgroup)
  {
    if (subnodes_[subgroup] == 0) {
      subnodes_[subgroup] = new ParamNode(subgroup);
    }

    return subnodes_[subgroup];
  }

private: // attributes

  /// Subnodes of the tree
  std::string name_;
  std::map<std::string, ParamNode *> subnodes_;

};

#endif /* PARAMETERS_PARAM_NODE_HPP */
