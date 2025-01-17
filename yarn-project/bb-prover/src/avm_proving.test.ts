import {
  MAX_L2_TO_L1_MSGS_PER_TX,
  MAX_NOTE_HASHES_PER_TX,
  MAX_NULLIFIERS_PER_TX,
  MAX_PUBLIC_CALLS_TO_UNIQUE_CONTRACT_CLASS_IDS,
  MAX_PUBLIC_DATA_UPDATE_REQUESTS_PER_TX,
  MAX_UNENCRYPTED_LOGS_PER_TX,
  VerificationKeyData,
} from '@aztec/circuits.js';
import { Fr } from '@aztec/foundation/fields';
import { createLogger } from '@aztec/foundation/log';
import {
  MockedAvmTestContractDataSource,
  simulateAvmTestContractGenerateCircuitInputs,
} from '@aztec/simulator/public/fixtures';

import fs from 'node:fs/promises';
import { tmpdir } from 'node:os';
import path from 'path';

import {
  type BBSuccess,
  BB_RESULT,
  generateAvmProof,
  generateAvmProofV2,
  verifyAvmProof,
  verifyAvmProofV2,
} from './bb/execute.js';
import { extractAvmVkData } from './verification_key/verification_key_data.js';

const TIMEOUT = 300_000;

describe('AVM WitGen, proof generation and verification', () => {
  it(
    'Should prove and verify bulk_testing v1',
    async () => {
      await proveAndVerifyAvmTestContract(
        'bulk_testing',
        /*args=*/ [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10].map(x => new Fr(x)),
      );
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify test that performs too many storage writes and reverts',
    async () => {
      await proveAndVerifyAvmTestContract(
        'n_storage_writes',
        /*args=*/ [new Fr(MAX_PUBLIC_DATA_UPDATE_REQUESTS_PER_TX + 1)],
        /*expectRevert=*/ true,
      );
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify test that creates too many note hashes and reverts',
    async () => {
      await proveAndVerifyAvmTestContract(
        'n_new_note_hashes',
        /*args=*/ [new Fr(MAX_NOTE_HASHES_PER_TX + 1)],
        /*expectRevert=*/ true,
      );
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify test that creates too many nullifiers and reverts',
    async () => {
      await proveAndVerifyAvmTestContract(
        'n_new_nullifiers',
        /*args=*/ [new Fr(MAX_NULLIFIERS_PER_TX + 1)],
        /*expectRevert=*/ true,
      );
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify test that creates too many l2tol1 messages and reverts',
    async () => {
      await proveAndVerifyAvmTestContract(
        'n_new_l2_to_l1_msgs',
        /*args=*/ [new Fr(MAX_L2_TO_L1_MSGS_PER_TX + 1)],
        /*expectRevert=*/ true,
      );
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify test that creates too many unencrypted logs and reverts',
    async () => {
      await proveAndVerifyAvmTestContract(
        'n_new_unencrypted_logs',
        /*args=*/ [new Fr(MAX_UNENCRYPTED_LOGS_PER_TX + 1)],
        /*expectRevert=*/ true,
      );
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify test that calls the max number of unique contract classes',
    async () => {
      const contractDataSource = new MockedAvmTestContractDataSource();
      // args is initialized to MAX_PUBLIC_CALLS_TO_UNIQUE_CONTRACT_CLASS_IDS contract addresses with unique class IDs
      const args = Array.from(contractDataSource.contractInstances.values())
        .map(instance => instance.address.toField())
        .slice(0, MAX_PUBLIC_CALLS_TO_UNIQUE_CONTRACT_CLASS_IDS);
      // include the first contract again again at the end to ensure that we can call it even after the limit is reached
      args.push(args[0]);
      // include another contract address that reuses a class ID to ensure that we can call it even after the limit is reached
      args.push(contractDataSource.instanceSameClassAsFirstContract.address.toField());
      await proveAndVerifyAvmTestContract(
        'nested_call_to_add_n_times_different_addresses',
        args,
        /*expectRevert=*/ false,
        /*skipContractDeployments=*/ false,
        contractDataSource,
      );
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify test that attempts too many calls to unique contract class ids',
    async () => {
      const contractDataSource = new MockedAvmTestContractDataSource();
      // args is initialized to MAX_PUBLIC_CALLS_TO_UNIQUE_CONTRACT_CLASS_IDS+1 contract addresses with unique class IDs
      // should fail because we are trying to call MAX+1 unique class IDs
      const args = Array.from(contractDataSource.contractInstances.values()).map(instance =>
        instance.address.toField(),
      );
      // push an empty one (just padding to match function calldata size of MAX_PUBLIC_CALLS_TO_UNIQUE_CONTRACT_CLASS_IDS+2)
      args.push(new Fr(0));
      await proveAndVerifyAvmTestContract(
        'nested_call_to_add_n_times_different_addresses',
        args,
        /*expectRevert=*/ true,
        /*skipContractDeployments=*/ false,
        contractDataSource,
      );
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify a top-level exceptional halt',
    async () => {
      await proveAndVerifyAvmTestContract('divide_by_zero', /*args=*/ [], /*expectRevert=*/ true);
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify a nested exceptional halt that propagates to top-level',
    async () => {
      await proveAndVerifyAvmTestContract('external_call_to_divide_by_zero', /*args=*/ [], /*expectRevert=*/ true);
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify a nested exceptional halt that is recovered from in caller',
    async () => {
      await proveAndVerifyAvmTestContract(
        'external_call_to_divide_by_zero_recovers',
        /*args=*/ [],
        /*expectRevert=*/ false,
      );
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify an exceptional halt due to a nested call to non-existent contract that is propagated to top-level',
    async () => {
      await proveAndVerifyAvmTestContract('nested_call_to_nothing', /*args=*/ [], /*expectRevert=*/ true);
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify an exceptional halt due to a nested call to non-existent contract that is recovered from in caller',
    async () => {
      await proveAndVerifyAvmTestContract('nested_call_to_nothing_recovers', /*args=*/ [], /*expectRevert=*/ false);
    },
    TIMEOUT,
  );
  it(
    'Should prove and verify a top-level exceptional halt due to a non-existent contract',
    async () => {
      await proveAndVerifyAvmTestContract(
        'add_args_return',
        /*args=*/ [new Fr(1), new Fr(2)],
        /*expectRevert=*/ true,
        /*skipContractDeployments=*/ true,
      );
    },
    TIMEOUT,
  );
});

async function proveAndVerifyAvmTestContract(
  functionName: string,
  args: Fr[] = [],
  expectRevert = false,
  skipContractDeployments = false,
  contractDataSource = new MockedAvmTestContractDataSource(skipContractDeployments),
) {
  const avmCircuitInputs = await simulateAvmTestContractGenerateCircuitInputs(
    functionName,
    args,
    expectRevert,
    contractDataSource,
  );

  const logger = createLogger('bb-prover:avm-proving-test');

  // The paths for the barretenberg binary and the write path are hardcoded for now.
  const bbPath = path.resolve('../../barretenberg/cpp/build/bin/bb');
  const bbWorkingDirectory = await fs.mkdtemp(path.join(tmpdir(), 'bb-'));

  // Then we prove.
  const proofRes = await generateAvmProof(bbPath, bbWorkingDirectory, avmCircuitInputs, logger);
  if (proofRes.status === BB_RESULT.FAILURE) {
    logger.error(`Proof generation failed: ${proofRes.reason}`);
  }
  expect(proofRes.status).toEqual(BB_RESULT.SUCCESS);

  // Then we test VK extraction and serialization.
  const succeededRes = proofRes as BBSuccess;
  const vkData = await extractAvmVkData(succeededRes.vkPath!);
  VerificationKeyData.fromBuffer(vkData.toBuffer());

  // Then we verify.
  const rawVkPath = path.join(succeededRes.vkPath!, 'vk');
  const verificationRes = await verifyAvmProof(bbPath, succeededRes.proofPath!, rawVkPath, logger);
  expect(verificationRes.status).toBe(BB_RESULT.SUCCESS);
}

describe('AVM WitGen, proof generation and verification', () => {
  it('Should prove and verify bulk_testing v2', async () => {
    const functionName = 'bulk_testing';
    const calldata = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10].map(x => new Fr(x));
    const avmCircuitInputs = await simulateAvmTestContractGenerateCircuitInputs(functionName, calldata, false);

    const logger = createLogger('bb-prover:avm-proving-test');

    // The paths for the barretenberg binary and the write path are hardcoded for now.
    const bbPath = path.resolve('../../barretenberg/cpp/build/bin/bb');
    const bbWorkingDirectory = await fs.mkdtemp(path.join(tmpdir(), 'bb-'));

    // Then we prove.
    const proofRes = await generateAvmProofV2(bbPath, bbWorkingDirectory, avmCircuitInputs, logger);
    if (proofRes.status === BB_RESULT.FAILURE) {
      logger.error(`Proof generation failed: ${proofRes.reason}`);
    }
    expect(proofRes.status).toEqual(BB_RESULT.SUCCESS);
    const succeededRes = proofRes as BBSuccess;

    // Then we verify.
    // Placeholder for now.
    const publicInputs = {
      dummy: [] as any[],
    };

    const rawVkPath = path.join(succeededRes.vkPath!, 'vk');
    const verificationRes = await verifyAvmProofV2(
      bbPath,
      bbWorkingDirectory,
      succeededRes.proofPath!,
      publicInputs,
      rawVkPath,
      logger,
    );
    expect(verificationRes.status).toBe(BB_RESULT.SUCCESS);
  }, 180_000);
});
