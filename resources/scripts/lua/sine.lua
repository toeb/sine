-- initializing


a=object1;


print(a.getValue1());
a:Lol();
-- print its public elements (none) print"Object fields"
for k,v in pairs(a) do
    print(" ", k, v)
end

-- print its metatable
print"Object metatable:"
for k,v in pairs(getmetatable(a)) do
    print("    ", k, v)
end

-- print its private table
print"Object private table:"
for k,v in pairs(rawget(getmetatable(a), "private")) do
    print("    ", k, v)
end

