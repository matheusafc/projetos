wage = float(input("\nDigite o salário bruto: R$ "))

if wage <= 1903.98:
    print("Imposto de Renda Retido na Fonte (IRRF): Isento")

elif wage > 1903.98 and wage <= 2826.65:
    irrf = (wage - 142.80) * 0.075
    wageLiquid = wage - irrf

elif wage > 2826.65 and wage <= 3751.05:
    irrf = (wage - 354.80) * 0.15
    wageLiquid = wage - irrf

elif wage > 3751.05 and wage <= 4664.68:
    irrf = (wage - 636.13) * 0.225
    wageLiquid = wage - irrf

else:
    irrf = (wage - 869.36) * 0.275
    wageLiquid = wage - irrf

print("\nTabela de IRRF de 04/2015 a 02/2022")
print(f"{'Base de Cálculo':<30} {'Aliquota':<10} {'Dedução':<10}")
print(f"{'de 0 até 1.903,98':<30} {'isento':<10} {'0,00':<10}")
print(f"{'de 1.903,99 até 2.826,65':<30} {'7,50%':<10} {'142,80':<10}")
print(f"{'de 2.826,66 até 3.751,05':<30} {'15,00%':<10} {'354,80':<10}")
print(f"{'de 3.751,06 até 4.664,68':<30} {'22,50%':<10} {'636,13':<10}")
print(f"{'a partir de 4.664,68':<30} {'27,50%':<10} {'869,36':<10}")
print("\nSalário Liquido: R${:.2f}".format(wageLiquid))
print("Imposto de Renda Retido na Fonte (IRRF): R${:.2f}".format(irrf))
