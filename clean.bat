
FOR /R "E:\code\dks_software" %%F IN (*~) DO (
      DEL %%F /q
)
FOR /R "E:\code\dks_software" %%F IN (*.swp) DO (
      DEL %%F /q
)




