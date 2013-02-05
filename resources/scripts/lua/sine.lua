-- initializing

function recurse(key, prev, table, depth)
if(depth>10)then return end
if type(table)=="table"then

 for k,v in pairs(table) do
	recurse(k,prev.."."..key,v,depth+1);
 end
else
	print(depth, prev.."."..key, table);

end
end



function pv(obj)
	if(type(obj)~="table")then return end
	for k,v in pairs(obj) do
		print(k ,v);
	end
end
--asd = function(self,object,...) print(object) end
--asd(1,2,3,45)

recurse("Types","",Class,0);

print("trying to construct a objcet");

print("class",Class.UserDataStruct2);
--print("newobject", Class.UserDataStruct2:new());
print("asdasdaSd");
--print("metatable", getmetatable(Class.UserDataStruct2:new()))
aasd = Class.UserDataStruct2:new();
--print("object againg",aasd);
print(aasd:Lol());
print(aasd:Value1());
print(aasd:Value2());
print(aasd:Value1(42));
print(aasd:Value2(43));
print(aasd:Value1());
print(aasd:Value2());
aasd.Lol();

aasd = Nil;

--aObject = Class.UserDataStruct2();
Class.UserDataStruct2.Lol.call();
Class.UserDataStruct2.Value1.get();
Class.UserDataStruct2.Value1.set();
print(Class.UserDataStruct2)
print(Class.UserDataStruct2.Lol)
print(Class.UserDataStruct2.Value1)
print(Class.UserDataStruct2.Value2)

b = aObject.getValue1();
print(b);
print("Ende des scripts");
print("Ende des scripts");
