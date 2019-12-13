#pragma once

class NodeID {
public:
	NodeID() = default;
	NodeID(int id_) : id(id_) {};
	NodeID(const NodeID& rhs) = default;
	bool operator==(const NodeID& rhs) const;
	bool operator<(const NodeID& rhs) const;
private:
	int id{};
};